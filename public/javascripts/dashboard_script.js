function switchState(dataString) {
  const runningMachine = document.querySelector("#running-machine");
  const arm1 = document.querySelector("#arm1");
  const arm2 = document.querySelector("#arm2");
  const cartSpeed = document.querySelector("#cart-speed");

  runningMachine.innerText = "On"
  runningMachine.parentElement.classList.add("on");
}

switchState();