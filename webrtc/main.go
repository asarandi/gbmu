package main

import (
	"context"
	"crypto/md5"
	"encoding/json"
	"fmt"
	"io"
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
		_, _, err := rtpSender.ReadRTCP()
		if err != nil {
			if err != io.EOF {
				log.Println(`ReadRTCP()`, err)
			}
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
				break loop
			}
		case b := <-peer.upload:
			players[peer.playerId].romHash = fmt.Sprintf(`%x`, md5.Sum(b))
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
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	peer := peersGet(id)
	if peer == nil {
		http.Error(w, `peer not found`, http.StatusForbidden)
		return
	}
	data, err := ioutil.ReadAll(r.Body)
	_ = r.Body.Close()
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	log.Println(`received data @`, r.Method, r.RequestURI, `length`, len(data))
	if peer.playerId == -1 {
		if r.RequestURI != `/answer` {
			http.Error(w, `must be a player`, http.StatusForbidden)
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
				http.Error(w, `no content`, http.StatusNoContent)
				return
			}
			//http.ServeContent(w, r, peer.romHash+`.sav`, time.Now(), bytes.NewReader(data))
			filename := fmt.Sprintf(`gbmu-%s-%d.sav`, players[peer.playerId].romHash, time.Now().Unix())
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
	dc, err := pc.CreateDataChannel(`events`, nil)
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
		playerId:      -1,
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
	save          chan []byte
	frameBlending chan bool
}

type player struct {
	peer          *peer
	romHash       string
	frameBlending bool
}

/* TODO: make a generic per-player-settings-channel with iota's */

func (p peer) String() string {
	return fmt.Sprintf("%#v %#v %#v", p.ua, p.remote, p.xfwd)
}

var (
	players    = [2]player{}
	playersMux = &sync.RWMutex{}
	peers      = map[uuid.UUID]*peer{}
	peersMux   = &sync.RWMutex{}
)

const (
	ctrlBusy byte = iota
	ctrlAvailable
	ctrlClaimReq
	ctrlClaimAck
	ctrlClaimNack
	ctrlConcedeReq
	ctrlConcedeAck
	ctrlConcedeNack
	ctrlSetJoypad
	ctrlSetFrameBlending
	unknown
)

func dcBroadcast(data []byte) {
	peersMux.Lock()
	defer peersMux.Unlock()
	for _, peer := range peers {
		_ = peer.dc.Send(data)
	}
}

func dcSendSeats(peer *peer) {
	dc := peer.dc
	for i := 0; i < 2; i++ {
		state := ctrlBusy
		if players[i].peer == nil {
			state = ctrlAvailable
		}
		dc.Send([]byte{state, byte(i)})
	}
}

/*

server to individual messages:
    - seat0, seat1 status

*/

func sendTime(peer *peer) {
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()
	done := make(chan bool)
	go func() {
		time.Sleep(20 * time.Second)
		done <- true
	}()
	for {
		select {
		case <-done:
			fmt.Println("Done!")
			return
		case t := <-ticker.C:
			fmt.Println("Current time: ", t)
			peer.dc.Send([]byte(t.String()))
		}
	}
}

func handleDataChannel(peer *peer) {
	dc := peer.dc
	label := dc.Label()
	dc.OnOpen(func() {
		log.Println(peer.id, `DataChannel`, label, `onOpen`)
		go dcSendSeats(peer)
		go sendTime(peer)

	})
	dc.OnMessage(func(msg webrtc.DataChannelMessage) {
		a := byte(255)
		if len(msg.Data) > 0 {
			a = msg.Data[0]
		}
		b := byte(255)
		if len(msg.Data) > 1 {
			b = msg.Data[1]
		}
		switch a {
		case ctrlClaimReq:
			if b > 1 || peer.playerId != -1 {
				dc.Send([]byte{ctrlClaimNack, b})
				return
			}
			playersMux.Lock()
			defer playersMux.Unlock()
			i := int(b)
			if players[i].peer == nil {
				players[i].peer = peer
				peer.playerId = i
				dcBroadcast([]byte{ctrlBusy, b})
				dc.Send([]byte{ctrlClaimAck, b})
			} else {
				dc.Send([]byte{ctrlClaimNack, b})
			}

		case ctrlConcedeReq:
			if b > 1 || peer.playerId != int(b) {
				dc.Send([]byte{ctrlConcedeNack, b})
				return
			}
			playersMux.Lock()
			defer playersMux.Unlock()
			i := int(b)
			players[i].peer = nil
			peer.playerId = -1
			dc.Send([]byte{ctrlConcedeAck, b})
			dcBroadcast([]byte{ctrlAvailable, b})

		case ctrlSetJoypad:
			if peer.playerId != -1 {
				SetInput(peer.playerId, b)
			}
		case ctrlSetFrameBlending:
			if peer.playerId != -1 {
				SetFrameBlending(peer.playerId, b != 0)
			}
		default:
			log.Println(`received`, a, `via data channel ?`)
		}
	})
	dc.OnClose(func() {
		log.Println(`player`, peer.id, `DataChannel`, label, `onClose`)
		i := peer.playerId
		if i == -1 {
			return
		}
		SetInput(i, 0)
		peer.playerId = -1
		peersDel(peer.id)
		playersMux.Lock()
		defer playersMux.Unlock()
		players[i].peer = nil
		go dcBroadcast([]byte{ctrlAvailable, byte(i)})
	})
	dc.OnError(func(err error) {
		log.Println(`player`, peer.id, `DataChannel`, label, `onError`, err)
	})
}

func onPeerAdded(peer *peer) {
	go handleDataChannel(peer)

	//	id := -1
	//	if players[0].peer == nil {
	//		id = 0
	//	} else if players[1].peer == nil {
	//		id = 1
	//	}
	//	peer.playerId = id
	//	if id == -1 {
	//		return
	//	}
	//	log.Println(`adding player id`, id)
	//	players[id].peer = peer
	//	//done := make(chan bool, 2)
	//	//go handleJoypad(peer, id, done)
	//	//<-done
	//	players[id].peer = nil
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
	http.HandleFunc(`/app.js`, serveFile(`app.js`))
	http.HandleFunc(`/app.css`, serveFile(`app.css`))
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
			log.Fatalln(err)
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
