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
	"strconv"
	"sync"
	"syscall"
	"time"

	"github.com/google/uuid"
	"github.com/pion/webrtc/v3"
)

type peer struct {
	id        uuid.UUID
	broadcast bool
	playerId  int
	serial    int
	pc        *webrtc.PeerConnection
	dc        *webrtc.DataChannel
	tracks    []*webrtc.TrackLocalStaticRTP
}

type player struct {
	peer          *peer
	romHash       string
	frameBlending bool
}

var (
	peerSerial = 0
	players    = [2]player{}
	playersMux = &sync.RWMutex{}
	peers      = map[uuid.UUID]*peer{}
	peersMux   = &sync.RWMutex{}

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
	ctrlReload
)

func httpHandler(w http.ResponseWriter, r *http.Request) {
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

	if r.RequestURI == `/answer` {
		answer := &webrtc.SessionDescription{}
		err := json.Unmarshal(data, answer)
		if err == nil {
			err = peer.pc.SetRemoteDescription(*answer)
		}
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
		}
		return
	}

	if peer.playerId == -1 {
		http.Error(w, `must be a player`, http.StatusForbidden)
		return
	}

	if r.RequestURI == `/upload` {
		romHash := fmt.Sprintf(`%x`, md5.Sum(data))
		players[peer.playerId].romHash = romHash
		SetCartridge(peer.playerId, data)
		event := fmt.Sprintf(`peer-%d, player-%d uploads rom %s`, peer.serial, peer.playerId, romHash)
		log.Println(event)
		go dcBroadcast([]byte(event))
		return
	}

	if r.RequestURI != `/save` {
		return
	}

	if r.Method == http.MethodGet {
		data := GetSavefile(peer.playerId)
		if len(data) == 0 {
			http.Error(w, `no content`, http.StatusNoContent)
			return
		}
		filename := fmt.Sprintf(`gbmu-%s-%d.sav`, players[peer.playerId].romHash, time.Now().Unix())
		w.Header().Set(`x-filename`, filename)
		w.Header().Set(`content-disposition`, `attachment; filename="`+filename+`"`)
		w.Header().Set(`content-type`, `application/octet-stream`)
		w.Header().Set(`content-length`, fmt.Sprintf(`%d`, len(data)))
		_, err = w.Write(data)
		event := fmt.Sprintf(`peer-%d, player-%d downloads ram`, peer.serial, peer.playerId)
		log.Println(event)
		go dcBroadcast([]byte(event))
	} else if r.Method == http.MethodPost {
		SetSavefile(peer.playerId, data)
		event := fmt.Sprintf(`peer-%d, player-%d uploads ram`, peer.serial, peer.playerId)
		log.Println(event)
		go dcBroadcast([]byte(event))
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
		id:       uuid.New(),
		playerId: -1,
		serial:   peerSerial,
		pc:       pc,
		dc:       dc,
		tracks:   tracks,
	}
	peerSerial++
	peersSet(peer.id, peer)
	w.Header()[`x-peer-id`] = []string{peer.id.String()}
	_ = json.NewEncoder(w).Encode(pc.LocalDescription())
	go waitForAnswer(peer)
	log.Println(`new peer!`, `id`, peer.id, `serial`, peer.serial, `ua`, r.UserAgent(), `remote`, r.RemoteAddr, `xfwd`, r.Header[`X-Forwarded-For`])
}

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

func waitForAnswer(peer *peer) {
	timeout := time.NewTimer(5 * time.Second)
	peer.pc.OnConnectionStateChange(func(state webrtc.PeerConnectionState) {
		log.Println(peer.id, "connection state", state.String())
		if state == webrtc.PeerConnectionStateConnected {
			for _, sender := range peer.pc.GetSenders() {
				go rtcpLoop(sender)
			}
			peer.broadcast = true
			go onPeerAdded(peer)
		} else if state > webrtc.PeerConnectionStateConnected {
			go onPeerLeaving(peer)
		}
	})
	<-timeout.C
	if !peer.broadcast {
		go onPeerLeaving(peer)
	}
}

func dcBroadcast(data []byte) {
	peersMux.Lock()
	defer peersMux.Unlock()
	for _, peer := range peers {
		_ = peer.dc.Send(data)
	}
}

func onPeerLeaving(peer *peer) {
	peersMux.Lock()
	defer peersMux.Unlock()
	if peer.pc == nil {
		return
	}

	log.Println(`onPeerLeaving()`, peer.id, `playerId`, peer.playerId)

	peer.dc.Close()
	peer.dc = nil
	peer.pc.Close()
	peer.pc = nil
	peer.broadcast = false
	delete(peers, peer.id)
	i := peer.playerId
	peer.playerId = -1

	event := fmt.Sprintf(`peer-%d left room. room has %d peers remaining.`, peer.serial, len(peers))
	log.Println(event)
	go dcBroadcast([]byte(event))

	if i == -1 {
		return
	}

	playersMux.Lock()
	defer playersMux.Unlock()

	SetInput(i, 0)
	players[i].peer = nil
	go dcBroadcast([]byte{ctrlAvailable, byte(i)})

	event = fmt.Sprintf(`peer-%d stopped playing. concedes player-%d controls`, peer.serial, i)
	log.Println(event)
	go dcBroadcast([]byte(event))

}

func onPeerAdded(peer *peer) {
	dc := peer.dc
	label := dc.Label()
	dc.OnOpen(func() {
		log.Println(peer.id, `DataChannel`, label, `onOpen`)
		for i := 0; i < 2; i++ {
			state := ctrlBusy
			if players[i].peer == nil {
				state = ctrlAvailable
			}
			dc.Send([]byte{state, byte(i)})
		}
		event := fmt.Sprintf(`peer-%d joins, room has %d peers`, peer.serial, len(peers))
		log.Println(event)
		go dcBroadcast([]byte(event))
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
				event := fmt.Sprintf(`peer-%d started playing. claims player-%d controls`, peer.serial, i)
				log.Println(event)
				go dcBroadcast([]byte(event))
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
			event := fmt.Sprintf(`peer-%d stopped playing. concedes player-%d controls`, peer.serial, i)
			log.Println(event)
			go dcBroadcast([]byte(event))

		case ctrlSetJoypad:
			if peer.playerId != -1 {
				SetInput(peer.playerId, b)
			}
		case ctrlSetFrameBlending:
			if peer.playerId != -1 {
				players[peer.playerId].frameBlending = b != 0
				SetFrameBlending(peer.playerId, b != 0)
				event := fmt.Sprintf(`player-%d has frame blending set to %t`, peer.playerId, b != 0)
				log.Println(event)
				go dcBroadcast([]byte(event))
			}
		case ctrlReload:
			if peer.playerId != -1 {
				ReloadBoth()
				event := fmt.Sprintf(`peer-%d, player-%d reloads both games`, peer.serial, peer.playerId)
				log.Println(event)
				go dcBroadcast([]byte(event))
			}
		default:
			s := string(msg.Data)
			ok := len(s) < 256
			if !ok {
				return
			}
			for _, c := range s {
				ok = ok && strconv.IsPrint(c)
			}
			if ok {
				event := fmt.Sprintf(`peer-%d: %s`, peer.serial, s)
				log.Println(event)
				go dcBroadcast([]byte(event))
			}
		}
	})
	dc.OnClose(func() {
		log.Println(`player`, peer.id, `DataChannel`, label, `onClose`)
		go onPeerLeaving(peer)
	})
	dc.OnError(func(err error) {
		log.Println(`player`, peer.id, `DataChannel`, label, `onError`, err)
	})
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
	http.HandleFunc(`/answer`, httpHandler)
	http.HandleFunc(`/upload`, httpHandler)
	http.HandleFunc(`/save`, httpHandler)
	http.Handle(`/`, http.FileServer(http.Dir(`web`)))

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
