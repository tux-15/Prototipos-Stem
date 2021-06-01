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

function sendAngle() {
    var a = document.getElementById("angleNumber").innerHTML = document.getElementById("angleValue").value;
    var ab = '#' + a;
    connection.send(ab)
  };

  function receiveSpeed(){}
