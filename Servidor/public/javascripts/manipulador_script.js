
var connection = new WebSocket('ws://' + location.hostname + ':1801/', ['arduino']);
connection.onopen = function () {
  connection.send(startPage());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
  receiveData(e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

let last = +new Date();

function sendAngle(slider, sliderValue) {
    document.getElementById(sliderValue).innerHTML = document.getElementById(slider).value;
    var command = {
      "slider": sliderValue,
      "angulo": document.getElementById(slider).value
    };

    commandJson = JSON.stringify(command);

    const now = +new Date();
    if (now - last > 50){
        last = now;
        connection.send(commandJson);
    };
};

function switchEffector(){
    var command = {"slider": "effector", "valor": "0"};
    commandJson = JSON.stringify(command);
    connection.send(commandJson);
};

function receiveData(data) {
    var complete_data = "Mensagem: " + data;
    document.getElementById("mensagem_manipulador").innerHTML = complete_data;
};

function startPage() {
  let id = getCookie("esp_id");
  let robot = getCookie("robot");
  startInfo = {
    "start": "page_on", 
    "to": id, 
    "meta": robot,
  };
  startInfoJson = JSON.stringify(startInfo);
  return startInfoJson;
};
  

function getCookie(cname) {
  var name = cname + "=";
  var decodedCookie = decodeURIComponent(document.cookie);
  var ca = decodedCookie.split(';');
  for(var i = 0; i <ca.length; i++) {
      var c = ca[i];
      while (c.charAt(0) == ' ') {
          c = c.substring(1);
      }
      if (c.indexOf(name) == 0) {
          return c.substring(name.length, c.length);
      };
  };
  return "";
};