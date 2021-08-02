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

function switchEffector(){
    var command = "<" + "effector, " + "0, " + "0>";
    connection.send(command);
}

function receiveData(data) {
    var complete_data = "Mensagemar: " + data;
    document.getElementById("mensagem_manipulador").innerHTML = complete_data;
}