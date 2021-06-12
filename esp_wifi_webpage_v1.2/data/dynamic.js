var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function () {
  connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function sendAngle(slider, sliderValue) {
    document.getElementById(sliderValue).innerHTML = document.getElementById(slider).value;
    var command = slider + ',' + sliderValue;
    connection.send(command)
  };

  function receiveSpeed(){}
