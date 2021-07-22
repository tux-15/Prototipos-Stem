var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function () {
  connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
  receiveData(e.data)
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

let last = +new Date();

function sendAngle(slider, sliderValue) {
    document.getElementById(sliderValue).innerHTML = document.getElementById(slider).value;
    var command = "<" + sliderValue + ',' + document.getElementById(slider).value + ">";
    const now = +new Date();
    if (now - last > 50){
        last = now;
        connection.send(command)
    }
  };

function sendPWM(leftInput, rightInput, valueLeft, valueRight, slider0, slider1) {
  document.getElementById(valueLeft).innerHTML = document.getElementById(leftInput).value;
  document.getElementById(valueRight).innerHTML = document.getElementById(rightInput).value;
  document.getElementById(slider0).value = document.getElementById(leftInput).value;
  document.getElementById(slider1).value = document.getElementById(rightInput).value;
  var pwm = "<" + 'carrinho' + ',' + document.getElementById(leftInput).value + "," + document.getElementById(rightInput).value + ">";
 
  connection.send(pwm)

}

function invertDirection() {
  var button = "<" + "inverter" + "," + "1" + ">";
  connection.send(button);
}

  // function receiveSpeed(){}

  function receiveData(data) {
    var complete_data = "RPM: " + data;
    document.getElementById("ws_test").innerHTML = complete_data;
  }
