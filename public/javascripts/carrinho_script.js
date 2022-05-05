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

function receiveData(received_data) {

    try{
      receiveData_json = JSON.parse(received_data);
      document.getElementById("rpm_direito").innerHTML = receiveData_json["speedR"];
      document.getElementById("rpm_esquerdo").innerHTML = receiveData_json["speedL"];
    }
    catch(err){
      console.log("Erro ao pegar o JSON: ", err);
      console.log("A mensagem recebida foi:", received_data);
    }
}

function send(x,y,speed,angle) {
  data = {
    "from": speed,
    "state": angle,
  };
  dataJson = JSON.stringify(data);
  console.log(dataJson);
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
  console.log(startInfoJson);
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