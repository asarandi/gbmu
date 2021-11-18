package main

import (
	"context"
	"crypto/md5"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"os/signal"
	"sync"
	"syscall"
	"time"

	"github.com/google/uuid"
	"github.com/pion/webrtc/v3"
)

var (
	pcConfig = webrtc.Configuration{
		ICEServers: []webrtc.ICEServer{{
			URLs: []string{"stun:stun.l.google.com:19302"},
		}}}

	audioCap = webrtc.RTPCodecCapability{
		MimeType:     webrtc.MimeTypeOpus,
		ClockRate:    48000,
		Channels:     2,
		SDPFmtpLine:  "",
		RTCPFeedback: nil,
	}

	videoCap = webrtc.RTPCodecCapability{
		MimeType: webrtc.MimeTypeH264,
	}
)

func rtcpLoop(rtpSender *webrtc.RTPSender) {
	for {
		_, _, rtcpErr := rtpSender.ReadRTCP()
		if rtcpErr != nil {
			log.Println("rtcpErr", rtcpErr)
			return
		}
	}
}

func peerLoop(peer *peer) {
	defer func() {
		peer.broadcast = false
		peersDel(peer.id)
		log.Println("peerLoop(): done", peer.id)
		err := peer.pc.Close()
		if err != nil {
			panic(err)
		}
	}()
	done := make(chan bool)
	timeout := time.NewTimer(5 * time.Second)
	peer.pc.OnConnectionStateChange(func(state webrtc.PeerConnectionState) {
		log.Println(peer.id, "connection state", state.String())
		if state == webrtc.PeerConnectionStateConnected {
			for _, sender := range peer.pc.GetSenders() {
				go rtcpLoop(sender)
			}
			peer.broadcast = true
			onPeerAdded(peer)
		} else if state > webrtc.PeerConnectionStateConnected {
			done <- true
		}
	})
loop:
	for {
		select {
		case b := <-peer.answer:
			answer := &webrtc.SessionDescription{}
			err := json.Unmarshal(b, answer)
			if err != nil {
				log.Println(err)
				break loop
			}
			err = peer.pc.SetRemoteDescription(*answer)
			if err != nil {
				log.Println(err)
			}
		case b := <-peer.upload:
			peer.romHash = fmt.Sprintf(`%x`, md5.Sum(b))
			SetCartridge(peer.playerId, b)
		case b := <-peer.save:
			SetSavefile(peer.playerId, b)
		case b := <-peer.frameBlending:
			SetFrameBlending(peer.playerId, b)
		case <-timeout.C:
			if !peer.broadcast {
				break loop
			}
		case <-done:
			break loop

		}
	}
}

func answer(w http.ResponseWriter, r *http.Request) {
	id, err := uuid.Parse(r.Header.Get(`x-peer-id`))
	if err != nil {
		log.Println(err)
		return
	}
	peer := peersGet(id)
	if peer == nil {
		log.Println(`peer not found`)
		return
	}
	data, err := ioutil.ReadAll(r.Body)
	_ = r.Body.Close()
	if err != nil {
		log.Println(err)
		return
	}
	log.Println(`received data @`, r.Method, r.RequestURI, `length`, len(data))
	if peer.playerId == -1 {
		if r.RequestURI != `/answer` {
			http.Error(w, ``, http.StatusForbidden)
			return
		}
	}
	switch r.RequestURI {
	case `/answer`:
		peer.answer <- data
	case `/reload`:
		ReloadBoth()
	case `/upload`:
		peer.upload <- data
	case `/save`:
		switch r.Method {
		case http.MethodPost:
			peer.save <- data
		case http.MethodGet:
			data := GetSavefile(peer.playerId)
			if len(data) == 0 {
				w.WriteHeader(http.StatusNoContent)
				return
			}
			//http.ServeContent(w, r, peer.romHash+`.sav`, time.Now(), bytes.NewReader(data))
			filename := fmt.Sprintf(`gbmu-%s-%d.sav`, peer.romHash, time.Now().Unix())
			w.Header().Set(`x-filename`, filename)
			w.Header().Set(`content-disposition`, `attachment; filename="`+filename+`"`)
			w.Header().Set(`content-type`, `application/octet-stream`)
			w.Header().Set(`content-length`, fmt.Sprintf(`%d`, len(data)))
			_, err = w.Write(data)
		}
	case `/frame-blending/0`:
		peer.frameBlending <- false
	case `/frame-blending/1`:
		peer.frameBlending <- true
	}
}

func offer(w http.ResponseWriter, r *http.Request) {
	pc, err := webrtc.NewPeerConnection(pcConfig)
	if err != nil {
		panic(err)
	}
	dc, err := pc.CreateDataChannel(`chat`, nil)
	if err != nil {
		panic(err)
	}
	tracks := make([]*webrtc.TrackLocalStaticRTP, 0)
	for _, t := range []struct {
		caps         webrtc.RTPCodecCapability
		id, streamId string
	}{
		{audioCap, `audio0`, `player0`},
		{videoCap, `video0`, `player0`},
		{audioCap, `audio1`, `player1`},
		{videoCap, `video1`, `player1`},
	} {
		track, err := webrtc.NewTrackLocalStaticRTP(t.caps, t.id, t.streamId)
		if err != nil {
			panic(err)
		}
		_, err = pc.AddTrack(track)
		if err != nil {
			panic(err)
		}
		tracks = append(tracks, track)
	}
	offer, err := pc.CreateOffer(nil)
	if err != nil {
		panic(err)
	}
	ice := webrtc.GatheringCompletePromise(pc)
	err = pc.SetLocalDescription(offer)
	if err != nil {
		panic(err)
	}
	<-ice
	peer := &peer{
		id:            uuid.New(),
		pc:            pc,
		dc:            dc,
		tracks:        tracks,
		answer:        make(chan []byte),
		upload:        make(chan []byte),
		save:          make(chan []byte),
		frameBlending: make(chan bool),
	}
	peersSet(peer.id, peer)
	go peerLoop(peer)
	w.Header()[`x-peer-id`] = []string{peer.id.String()}
	_ = json.NewEncoder(w).Encode(pc.LocalDescription())
}

type peer struct {
	id            uuid.UUID
	ua            string
	remote        string
	xfwd          string
	broadcast     bool
	isPlayer      bool
	playerId      int
	pc            *webrtc.PeerConnection
	dc            *webrtc.DataChannel
	tracks        []*webrtc.TrackLocalStaticRTP
	answer        chan []byte
	upload        chan []byte
	romHash       string
	save          chan []byte
	frameBlending chan bool
}

/* TODO: make a generic per-player-settings-channel with iota's */

func (p peer) String() string {
	return fmt.Sprintf("%#v %#v %#v", p.ua, p.remote, p.xfwd)
}

var (
	players  = [2]*peer{nil, nil}
	peers    = map[uuid.UUID]*peer{}
	peersMux = &sync.RWMutex{}
)

func handleJoypad(peer *peer, playerId int, done chan bool) {
	dc, err := peer.pc.CreateDataChannel(`joypad`, nil)
	if err != nil {
		log.Println(`player`, playerId, `CreateDataChannel`, err)
		done <- true
		return
	}
	label := dc.Label()
	dc.OnOpen(func() {
		log.Println(`player`, playerId, `DataChannel`, label, `onOpen`)
	})
	dc.OnMessage(func(msg webrtc.DataChannelMessage) {
		SetInput(playerId, msg.Data[0])
	})
	dc.OnClose(func() {
		log.Println(`player`, playerId, `DataChannel`, label, `onClose`)
		SetInput(playerId, 0)
		done <- true
	})
	dc.OnError(func(err error) {
		log.Println(`player`, playerId, `DataChannel`, label, `onError`, err)
	})
}

func onPeerAdded(peer *peer) {
	id := -1
	if players[0] == nil {
		id = 0
	} else if players[1] == nil {
		id = 1
	}
	peer.playerId = id
	if id == -1 {
		return
	}
	log.Println(`adding player id`, id)
	players[id] = peer
	done := make(chan bool, 2)
	go handleJoypad(peer, id, done)
	<-done
	players[id] = nil
}

func peersGet(key uuid.UUID) *peer {
	peersMux.Lock()
	defer peersMux.Unlock()
	return peers[key]
}

func peersSet(key uuid.UUID, value *peer) {
	peersMux.Lock()
	defer peersMux.Unlock()
	peers[key] = value
}

func peersDel(key uuid.UUID) {
	peersMux.Lock()
	defer peersMux.Unlock()
	delete(peers, key)
}

func serveFile(f string) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, f)
	}
}

func main() {
	done := make(chan bool)
	go emulator(done)

	http.HandleFunc(`/offer`, offer)
	http.HandleFunc(`/answer`, answer)
	http.HandleFunc(`/upload`, answer)
	http.HandleFunc(`/save`, answer)
	http.HandleFunc(`/reload`, answer)
	http.HandleFunc(`/frame-blending/0`, answer)
	http.HandleFunc(`/frame-blending/1`, answer)
	http.HandleFunc(`/`, serveFile(`index.html`))

	server := &http.Server{
		Addr:         `:8080`,
		WriteTimeout: 15 * time.Second,
		ReadTimeout:  15 * time.Second,
		IdleTimeout:  15 * time.Second,
	}

	go func() {
		log.Println(`listening @`, server.Addr)
		err := server.ListenAndServe()
		if err != nil {
			log.Println(err)
		}
	}()

	sig := make(chan os.Signal, 1)
	signal.Notify(sig, syscall.SIGINT, syscall.SIGKILL, syscall.SIGTERM)
	<-sig
	done <- true

	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel()
	err := server.Shutdown(ctx)
	if err != nil {
		log.Println(err)
	}
}
