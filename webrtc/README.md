# webrtc

__build__, __run__  then open [`http://localhost:8080/`](http://localhost:8080/) in your browser

## native
### build
```
make webrtc
```
### run
```
./gbmu
```

## docker
### build
```
make docker
```
### run
```
docker run -p8080:8080 gbmu
```

---


# instructions:
- for best experience please use desktop computer with latest mozilla firefox browser
- the indicator in the top-left corner of the page should be green and say "connected"
- if the indicator is black and/or says "failed" please try a different device/connection
- please allow 10 seconds for the page to load fully: two videos should appear
- unmute the videos to enable sound
- press the "play" button to become a player and enable game controls (see below)
- when you become a player, other buttons will become enabled: "upload rom", "upload ram"
- when you're done playing, press the "quit" button to concede the game controls
- press the "upload rom" button to select a gameboy rom file (.gb, .gbc) from your local disk
- press the "upload ram" button to select a gameboy save file (.sav) from your local disk
- netplay/multiplayer: ask a friend to join as player-2 and upload the same rom
- multiplayer games list: https://en.wikipedia.org/wiki/List_of_multiplayer_Game_Boy_games
- there is a simple chat at the bottom of the page, it also shows system events


# notes about chrome/chromium:
- video is not pixelated:
  server sends video with 160x144 resolution,
  when using the "scale" option video looks blurry,
  video elements have CSS property "image-rendering: pixelated" -
  but it seems like chrome does not honor this property for video elements.
  works as expected in firefox - scaled video looks nice and sharp,
  see screenshot for side by side comparison: https://i.imgur.com/NP6QGRl.png
- audio is mono (instead of stereo):
  description: opus audio is always rendered as "mono" in google chrome
  https://bugs.chromium.org/p/webrtc/issues/detail?id=8133
  TODO (alex): try SDP munging workaround
  works as expected in firefox
- sound stops playing:
  issue: pressing down arrow key slides the volume control down
  workaround: click away from video to prevent
  works as expected in firefox


# game controls [gameboy => web browser]:
d-pad  => arrow keys
b, a   => z, x
start  => return
select => right shift
