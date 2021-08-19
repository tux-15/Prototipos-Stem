var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function () {
  connection.send('Connect ' + new Date());
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
    // let data = received_data;
    // let parsed_data = data.split(",");

    // let mensagem = parsed_data[0];

    // let rpm_esquerda = parsed_data[1];
    // let rpm_direita = parsed_data[2];

    // let vel_esquerda = parsed_data[3];
    // let vel_direita = parsed_data[4];

    // var rpm_data = "RPM Esquerdo: " + rpm_esquerda + " RPM Direito: " + rpm_direita;
    // var vel_data = "Velocidade esquerda: " + vel_esquerda + " Velocidade direita: " + vel_direita;
    // document.getElementById("rpm").innerHTML = rpm_data;
    // document.getElementById("velocidade").innerHTML = vel_data;
    document.getElementById("dados_carrinho").innerHTML = received_data;
}

function getVel(received_data){
    let data = receivedData;
    let parsed_data = data.split(",");
    if (parsed_data[0] == "velocidade_media"){
        document.getElementById("velocidade_joystick").innerHTML = parsed_data[1];
    }
}

function invertDirection(){
    var button = "<" + "inverter" + "," + "1" + ">";
    connection.send(button);
}

function sendPWM(leftInput, rightInput, valueLeft, valueRight, slider0, slider1) {
    document.getElementById(valueLeft).innerHTML = document.getElementById(leftInput).value;
    document.getElementById(valueRight).innerHTML = document.getElementById(rightInput).value;
    document.getElementById(slider0).value = document.getElementById(leftInput).value;
    document.getElementById(slider1).value = document.getElementById(rightInput).value;
    var pwm = "<" + 'carrinho' + ',' + document.getElementById(leftInput).value + "," + document.getElementById(rightInput).value + ">";

    connection.send(pwm);

}

function sendAngle(slider, sliderValue) {
    document.getElementById(sliderValue).innerHTML = document.getElementById(slider).value;
    var command = "<" + sliderValue + ',' + document.getElementById(slider).value + ">";
    const now = +new Date();
    if (now - last > 50){
        last = now;
        connection.send(command);
    }
};

function send(x,y,speed,angle){
  data = '<' + 'carrinho, ' + speed + ', ' + angle + '>'
  connection.send(data);
}