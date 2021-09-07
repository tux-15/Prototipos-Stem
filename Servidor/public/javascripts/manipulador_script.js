
var connection = new WebSocket('ws://' + location.hostname + ':1801/', ['arduino']);
connection.onopen = function () {
  // connection.send('Connect ' + new Date());
  connection.send('page_on');
  // connection.send(sendJson());
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
        connection.send(command);
    }
};

function switchEffector(){
    var command = "<" + "effector, " + "0, " + "0>";
    connection.send(command);
};

function receiveData(data) {
    var complete_data = "Mensagem: " + data;
    document.getElementById("mensagem_manipulador").innerHTML = complete_data;
};


function sendCookie() {
  let id = getCookie("esp_id");
  let robot = getCookie("robot");
  if (id != "") {
    info = {"esp_id": id, "robot": robot};
    infoJson = JSON.stringify(info);
    return(infoJson);
    // console.log(connection);
  } 
} 

function sendJson() {
  let id = getCookie("esp_id");
  let robot = getCookie("robot");
  a = {"start": "page_on", "esp_id": id, "robot": robot};
  aa = JSON.stringify(a);
  return aa;
}
  

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
      }
  }
  return "";
}