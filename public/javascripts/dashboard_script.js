/* 
  {"from": "car", "state": "atM1"}; --> GIF1 -- M1 = ON / Esteira = OFF ;
  {"from": "car", "state": "toM2"}; --> GIF2 -- M1 = OFF ;
  {"from": "car", "state": "atM2"}; --> GIF3 -- M2 = ON ;
  {"from": "s2", "state": "nearM2"}; --> GIF4 -- M2 = OFF / Esteira = ON

  {"from":"car", "speed": 4}
*/

const { json } = require("express/lib/response");

var connection = new WebSocket("ws://" + location.hostname + ":1801/", [
  "arduino",
]);

connection.onopen = function () {
  connection.send(startPage());
};

connection.onerror = function (error) {
  console.log("WebSocket Error ", error);
};

connection.onmessage = function (e) {
  console.log("Server: ", e.data);
  const prototypeData = JSON.parse(e.data);

  if (prototypeData.speed) {
    handleCartSpeed(prototypeData.speed);
  } else {
    // States: atM1(Gif1), toM2(Gif2), atM2(Gif3), nearM2(Gif4), undefined(cartSpeed)
    try {
      switch (prototypeData.state) {
        case "atM1":
          handleAtM1State();
          break;
        case "toM2":
          handleToM2State();
          break;
        case "atM2":
          handleAtM2State();
          break;
        case "nearM2":
          handleNearM2State();
          break;
        default:
          throw new Error("Invalid State");
      }
    } catch (err) {
      console.log(err);
    }
  }
};

connection.onclose = function () {
  console.log("WebSocket connection closed");
};

function handleAtM1State() {
  playAnimationGif("gif1");
  renderStateOfArm1("on");
  renderStateOfRunningMachine("off");
}

function handleToM2State() {
  playAnimationGif("gif2");
  renderStateOfArm1("off");
}

function handleAtM2State() {
  playAnimationGif("gif3");
  renderStateOfArm2("on");
}

function handleNearM2State() {
  playAnimationGif("gif4");
  renderStateOfRunningMachine("on");
  renderStateOfArm2("off");
}

function handleCartSpeed(speed) {
  renderCartSpeed("on", speed);
}

function playAnimationGif(gifName) {
  const prototypeGif = document.querySelector("#prototype-gif");
  const path = "http://localhost:5000/images/dashboard/";

  prototypeGif.src = `${path}${gifName}.gif`;
}

function changePrototypeCardState(element, state) {
  if (state === "on") {
    element.innerText = "On";
    element.parentElement.classList.add("on");
  } else {
    element.innerText = "Off";
    element.parentElement.classList.remove("on");
  }
}

function renderStateOfRunningMachine(state) {
  const runningMachine = document.querySelector("#running-machine");
  changePrototypeCardState(runningMachine, state);
}

function renderStateOfArm1(state) {
  const arm1 = document.querySelector("#arm1");
  changePrototypeCardState(arm1, state);
}

function renderStateOfArm2(state) {
  const arm2 = document.querySelector("#arm2");
  changePrototypeCardState(arm2, state);
}

function renderCartSpeed(state, speed) {
  const cartSpeed = document.querySelector("#cart-speed");
  cartSpeed.innerText = speed;

  if (state === "on") {
    cartSpeed.parentElement.classList.add("on");
  } else {
    cartSpeed.parentElement.classList.remove("on");
  }
}

function startPage() {
  let id = getCookie("esp_id");
  let robot = getCookie("robot");
  startInfo = {
    start: "page_on",
    to: id,
    meta: robot,
  };
  startInfoJson = JSON.stringify(startInfo);
  return startInfoJson;
}

function getCookie(cname) {
  var name = cname + "=";
  var decodedCookie = decodeURIComponent(document.cookie);
  var ca = decodedCookie.split(";");
  for (var i = 0; i < ca.length; i++) {
    var c = ca[i];
    while (c.charAt(0) == " ") {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}