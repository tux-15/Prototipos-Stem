async function findPrototypeData() {

  const response = await fetch("javascripts/json.json");
  const prototypeData = await response.json();

  console.log(prototypeData)
}

function changePrototypeCardState(element, state) {
  if (state === "on") {
    element.innerText = "On";
    element.parentElement.classList.add("on");
  } else {
    element.innerText = "Off";
    element.parentElement.classList.remove("on")
  }
}

function renderStateOfRunningMachine(state) {
  const runningMachine = document.querySelector("#running-machine");
  changePrototypeCardState(runningMachine, state);
}

function renderStateOfArm1(state) {
  const arm1 = document.querySelector("#arm1");
  changePrototypeCardState(arm1, state);
};

function renderStateOfArm2(state) {
  const arm2 = document.querySelector("#arm2");
  changePrototypeCardState(arm2, state);
};

function renderVelocityOfCar(speed) {
  const cartSpeed = document.querySelector("#cart-speed");
  
};

findPrototypeData();