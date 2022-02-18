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
  receiveData(e.data);
  playAnimation(e.data);
};
connection.onclose = function () {

  console.log("WebSocket connection closed");
};

function playAnimation(data){
  dado = JSON.parse(data);

  /* 
  {"from": "car", "state": "atM1"}; --> GIF1 -- M1 = ON / Esteira = OFFF
  {"from": "car", "state": "toM2"}; --> GIF2 -- M1 = OFF
  {"from": "car", "state": "atM2"}; --> GIF3 -- M2 = ON
  {"from": "s2", "state": "nearM2"}; --> GIF4 -- M2 = OFF / Esteira = ON

  {"from":"car", "speed": 4}

  */

}

function receiveData(data) {
  dado = JSON.parse(data)
  var complete_data = "Mensagem: " + data;
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

async function findPrototypeData() {
  const response = await fetch("javascripts/json.json");
  const prototypeData = await response.json();

  return prototypeData;
}

function renderPrototypeData(prototypeData) {
  const {
    runningMachineState,
    arm1State,
    arm2State,
    cart: { cartState, cartSpeed },
  } = prototypeData;

  renderStateOfRunningMachine(runningMachineState);
  renderStateOfArm1(arm1State);
  renderStateOfArm2(arm2State);
  renderVelocityOfCar(cartState, cartSpeed);
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

function renderVelocityOfCar(state, speed) {
  const cartSpeed = document.querySelector("#cart-speed");
  cartSpeed.innerText = speed;

  if (state === "on") {
    cartSpeed.parentElement.classList.add("on");
  } else {
    cartSpeed.parentElement.classList.remove("on");
  }
}

findPrototypeData().then((prototypeData) => renderPrototypeData(prototypeData));
