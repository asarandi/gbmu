"use strict";

let dataChannel = null;
let peerId = "";
let ctrlState = [0, 0];

const setClaimButton = (i, s) => {
  const ids = ["#claim0", "#claim1"];
  const states = ["busy", "play", "quit"];
  let elem = document.querySelector(ids[i]);
  elem.innerText = states[s];
  if (s === 0) {
    elem.setAttribute("disabled", "true");
  } else {
    elem.removeAttribute("disabled");
  }
};

const enablePlayer = (enabled) => {
  document.querySelectorAll(".player").forEach((elem) => {
    if (!enabled) {
      elem.setAttribute("disabled", "true");
    } else {
      elem.removeAttribute("disabled");
    }
  });
};

const activePlayerIndicator = () => {
  for (let i = 0; i < 2; i++) {
    const elem = document.querySelector(`video#player${i}`);
    if (ctrlState[i] == 2) {
      elem.classList.add("active-player");
    } else {
      elem.classList.remove("active-player");
    }
  }
};

const connect = () => {
  const pcConfig = {
    iceServers: [{ urls: "stun:stun.l.google.com:19302" }],
  };

  const pc = new RTCPeerConnection(pcConfig);

  fetch("/offer", { method: "get" })
    .then((response) => {
      peerId = response.headers.get("x-peer-id");
      return response.json();
    })
    .then((offer) => pc.setRemoteDescription(new RTCSessionDescription(offer)))
    .then(() => pc.createAnswer())
    .then((answer) => pc.setLocalDescription(answer))
    .catch(console.error);
  pc.onicecandidate = (event) => {
    if (event.candidate === null) {
      fetch("/answer", {
        method: "post",
        headers: { "x-peer-id": peerId },
        body: JSON.stringify(pc.localDescription),
      });
    }
  };

  pc.onconnectionstatechange = (event) => {
    console.log(`onConnectionStateChange: ${pc.connectionState}`);
    const setIndicator = (message, color) => {
      const image = document.querySelector("span#indicatorImage");
      image.style = `width: 1rem; height: 1rem; border-radius: 50%; display: inline-block; background-color: ${color};`;
      const text = document.querySelector("span#indicatorText");
      text.style = `display: inline-block;`;
      text.innerText = message;
    };
    switch (pc.connectionState) {
      case "connected":
        setIndicator(pc.connectionState, "green");
        break;
      case "disconnected":
        setIndicator(pc.connectionState, "red");
        break;
      case "failed":
        setIndicator(pc.connectionState, "black");
        break;
      case "closed":
        setIndicator(pc.connectionState, "grey");
        break;
      default:
        setIndicator(pc.connectionState, "orange");
        break;
    }
  };

  pc.oniceconnectionstatechange = (event) => {
    console.log("onIceConnectionStateChange", pc.iceConnectionState);
  };

  pc.ontrack = (event) => {
    console.log("Got track event", event);
    for (let i = 0; i < event.streams.length; i++) {
      const streamId = event.streams[i].id;
      const elem = document.getElementById(streamId);
      if (elem) {
        elem.srcObject = event.streams[i];
      }
    }
  };

  const messages = [null, null, null, null, null, null, null, null];
  let mi = 0;
  const newMessage = (s) => {
    messages[mi] = s;
    const elem = document.querySelector("#messages");
    elem.innerText = ``;
    for (let i = 0; i < messages.length; i++) {
      let j = (mi + messages.length - i) % messages.length;
      if (!messages[j]) continue;
      elem.innerText += `${messages[j]}\n`;
    }
    mi = (mi + 1) % messages.length;
  };

  pc.ondatachannel = (event) => {
    event.channel.onopen = () => {
      console.log(`data channel`, `onOpen`, event.channel.label);
      if (event.channel.label === `events`) {
        dataChannel = event.channel;
        event.channel.binaryType = "arraybuffer";
      }
    };
    event.channel.onclose = () => {
      console.log(`data channel`, `onClose`, event.channel.label);
    };
    event.channel.onmessage = (msg) => {
      const data = new Uint8Array(msg.data);
      const a = data.length > 0 ? data[0] : 255;
      const b = data.length > 1 ? data[1] : 255;
      switch (a) {
        case 0: // ctrlBusy 0
          setClaimButton(b, 0); // "busy"
          ctrlState[b] = 0;
          break;
        case 1: // ctrlAvailable 1
          setClaimButton(b, 1); // "play"
          ctrlState[b] = 1;
          break;
        case 2: // ctrlClaimReq 2
          break;
        case 3: // ctrlClaimAck 3
          setClaimButton(b, 2); // peer became player, text becomes "quit"
          ctrlState[b] = 2;
          enablePlayer(true);
          activePlayerIndicator();
          break;
        case 4: // ctrlClaimNack 4
          break;
        case 5: // ctrlConcedeReq 5
          break;
        case 6: // ctrlConcedeAck 6
          setClaimButton(b, 0); // player conceded game, ctrl available
          ctrlState[b] = 0;
          enablePlayer(false);
          activePlayerIndicator();
          break;
        case 7: // ctrlConcedeNack 7
          break;
        case 8: // ctrlSetJoypad 8
          break;
        case 9: // ctrlSetFrameBlending 9
          break;
        case 10: // ctrlReload 10
          break;
        default:
          newMessage(String.fromCharCode.apply(null, data));
      }
    };
    event.channel.onerror = (err) => {
      console.log(`data channel`, `onError`, event.channel.label, err);
    };
  };
};

const keyMapping = {
  40: 0x80, //PADF_DOWN
  38: 0x40, //PADF_UP
  37: 0x20, //PADF_LEFT
  39: 0x10, //PADF_RIGHT
  13: 0x08, //PADF_START
  16: 0x04, //PADF_SELECT
  90: 0x02, //PADF_B
  88: 0x01, //PADF_A
};

let joyBefore = 0;
let joyAfter = 0;
const updateJoypad = () => {
  if (!dataChannel) return;
  if (joyBefore !== joyAfter) {
    // ctrlSetJoypad 8
    dataChannel.send(new Uint8Array([8, joyAfter]));
  }
  joyBefore = joyAfter;
};

const setupEventListeners = () => {
  const chatInput = document.querySelector("input#chatMessage");
  const encoder = new TextEncoder("utf-8");

  const sendChatMessage = () => {
    if (!encoder) return;
    if (!dataChannel) return;
    const data = encoder.encode(chatInput.value.trim());
    chatInput.value = ``;
    if (!data.length) return;
    if (data.length < 256) {
      dataChannel.send(data);
    }
  };

  let isChatFocus = false;
  chatInput.addEventListener("focus", (event) => {
    isChatFocus = true;
  });
  chatInput.addEventListener("blur", (event) => {
    isChatFocus = false;
  });
  chatInput.addEventListener("keydown", (event) => {
    if (event.keyCode === 13) sendChatMessage();
  });

  document
    .querySelector("button#chatSend")
    .addEventListener("click", sendChatMessage);

  const body = document.querySelector("body");
  body.addEventListener("keydown", (event) => {
    if (isChatFocus) return;
    if (event.keyCode in keyMapping) {
      event.preventDefault();
      joyAfter |= keyMapping[event.keyCode];
      joyAfter &= joyAfter & 0x80 ? ~0x40 : 0xff;
      joyAfter &= joyAfter & 0x20 ? ~0x10 : 0xff;
      updateJoypad();
    }
  });

  body.addEventListener("keyup", (event) => {
    if (isChatFocus) return;
    if (event.keyCode in keyMapping) {
      event.preventDefault();
      joyAfter &= ~keyMapping[event.keyCode];
      updateJoypad();
    }
  });

  const romInput = document.querySelector("input#romInput");
  romInput.addEventListener(
    "change",
    (event) => {
      if (romInput.files.length !== 1) {
        return;
      }
      const file = romInput.files[0];
      const n = file.size;
      if (!(32768 <= n && n <= 4194304 && (n & (n - 1)) === 0)) {
        console.error("unsupported file size", n);
        return;
      }
      file
        .arrayBuffer()
        .then((buffer) => {
          return fetch("/upload", {
            method: "post",
            headers: { "x-peer-id": peerId },
            body: buffer,
          });
        })
        .then((response) => {
          console.log("upload done!", response.status);
        })
        .catch(console.error);
    },
    false
  );

  const uploadRom = document.querySelector("button#uploadRom");
  uploadRom.addEventListener("click", (event) => {
    romInput.click();
  });

  const ramInput = document.querySelector("input#ramInput");
  ramInput.addEventListener(
    "change",
    (event) => {
      if (ramInput.files.length !== 1) {
        return;
      }
      const file = ramInput.files[0];
      const n = file.size;
      if (!(512 <= n && n <= 131072)) {
        console.error("unsupported ram file size", n);
        return;
      }
      file
        .arrayBuffer()
        .then((buffer) => {
          return fetch("/save", {
            method: "post",
            headers: { "x-peer-id": peerId },
            body: buffer,
          });
        })
        .then((response) => {
          console.log("ram upload done!", response.status);
        })
        .catch(console.error);
    },
    false
  );

  const uploadRam = document.querySelector("button#uploadRam");
  uploadRam.addEventListener("click", (event) => {
    ramInput.click();
  });

  const ramDownload = document.querySelector("a#ramDownload");
  const ramOutput = document.querySelector("button#ramOutput");
  ramOutput.addEventListener(
    "click",
    (event) => {
      fetch("/save", {
        method: "get",
        headers: { "x-peer-id": peerId },
      })
        .then((response) => {
          if (response.status === 200) {
            return Promise.all([
              response.blob(),
              response.headers.get(`x-filename`),
            ]);
          } else {
            return Promise.reject(new Error(response.statusText));
          }
        })
        .then((data) => {
          return Promise.all([URL.createObjectURL(data[0]), data[1]]);
        })
        .then((data) => {
          ramDownload.href = data[0];
          ramDownload.download = data[1];
          ramDownload.click();
          URL.revokeObjectURL(data[0]);
          ramDownload.href = ``;
          ramDownload.download = ``;
        })
        .catch(console.error);
    },
    false
  );

  const reload = document.querySelector("button#reload");
  reload.addEventListener(
    "click",
    (event) => {
      if (!dataChannel) return;
      // ctrlReload 10
      dataChannel.send(new Uint8Array([10]));
    },
    false
  );

  const frameBlending = document.querySelector("input#frame-blending");
  frameBlending.addEventListener(
    "change",
    (event) => {
      if (!dataChannel) return;
      // ctrlFrameBlending 9
      dataChannel.send(new Uint8Array([9, event.target.checked]));
    },
    false
  );

  const scale = document.querySelector("select#scale");
  scale.addEventListener(
    "change",
    (event) => {
      const val = parseInt(event.target.value, 10);
      document.querySelectorAll("video").forEach((element) => {
        element.style = `
      		image-rendering: pixelated!important;
      		width: ${val * 160}px!important;
      		height: ${val * 144}px!important;`;
      });
    },
    false
  );

  const claimControls = (i) => {
    if (!dataChannel) return;
    if (ctrlState[i] == 1) {
      // ctrlClaimReq 2
      dataChannel.send(new Uint8Array([2, i]));
    } else if (ctrlState[i] == 2) {
      // ctrlConcedeReq 5
      dataChannel.send(new Uint8Array([5, i]));
    }
  };

  const claim0 = document.querySelector("button#claim0");
  claim0.addEventListener("click", (event) => {
    claimControls(0);
  });

  const claim1 = document.querySelector("button#claim1");
  claim1.addEventListener("click", (event) => {
    claimControls(1);
  });
};

window.addEventListener("DOMContentLoaded", (event) => {
  enablePlayer(false);
  setClaimButton(0, 0);
  setClaimButton(1, 0);
  setupEventListeners();
  connect();
});
