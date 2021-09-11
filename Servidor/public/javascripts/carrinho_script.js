var connection = new WebSocket('ws://' + location.hostname + ':1801/', ['arduino']);
connection.onopen = function () {
  connection.send(startPage());

};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
  //receiveData(e.data) 
  //getVel(e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function receiveData(received_data) {
    document.getElementById("dados_carrinho").innerHTML = received_data;
}

function send(x,y,speed,angle){
  data = {
    "meta": "carrinho",
    "speed": speed,
    "angle": angle,
  };
  dataJson = JSON.stringify(data);
  connection.send(dataJson);
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
      }
  }
  return "";
}