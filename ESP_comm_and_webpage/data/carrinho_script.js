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

function receiveData(data) {
    var parsed_data = data.split(",");
    var mensagem = parsed_data[0];
    var int1 = parsed_data[1];
    var int2 = parsed_data[2];
    var complete_data = "RPM: " + data;
    document.getElementById("ws_test").innerHTML = complete_data;
}

function invertDirection() {
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
        connection.send(command)
    }
};

function send(x,y,speed,angle){
  // var data = {"x":x,"y":y,"speed":speed,"angle":angle};
  // data = JSON.stringify(data);
  // console.log(data);
  // connection.send(data);
  //var vel = document.getElementById("speed").innerHTML;
  //var angulo = document.getElementById("angle").innerHTML;
  //data = '<' + 'placeholder, ' + x + ', ' + y + ', ' + speed + ', ' + angle + '>'
  data = '<' + 'carrinho, ' + speed + ', ' + angle + '>'
  console.log(data);
  connection.send(data);
}

var canvas, ctx;
  let last = +new Date();

  window.addEventListener('load', () => {

      canvas = document.getElementById('canvas');
      ctx = canvas.getContext('2d');          
      resize(); 

      document.addEventListener('mousedown', startDrawing);
      document.addEventListener('mouseup', stopDrawing);
      document.addEventListener('mousemove', Draw);

      document.addEventListener('touchstart', startDrawing);
      document.addEventListener('touchend', stopDrawing);
      document.addEventListener('touchcancel', stopDrawing);
      document.addEventListener('touchmove', Draw);
      window.addEventListener('resize', resize);

      document.getElementById("x_coordinate").innerText = 0;
      document.getElementById("y_coordinate").innerText = 0;
      document.getElementById("speed").innerText = 0;
      document.getElementById("angle").innerText = 0;
  });

  var width, height, radius, x_orig, y_orig;
  function resize() {
      width = window.innerWidth;
      radius = 200;
      height = radius * 6.5;
      ctx.canvas.width = width;
      ctx.canvas.height = height;
      background();
      joystick(width / 2, height / 3);
  }

  function background() {
      x_orig = width / 2;
      y_orig = height / 3;

      ctx.beginPath();
      ctx.arc(x_orig, y_orig, radius + 20, 0, Math.PI * 2, true);
      ctx.fillStyle = '#ECE5E5';
      ctx.fill();
  }

  function joystick(width, height) {
      ctx.beginPath();
      ctx.arc(width, height, radius, 0, Math.PI * 2, true);
      ctx.fillStyle = '#F08080';
      ctx.fill();
      ctx.strokeStyle = '#F6ABAB';
      ctx.lineWidth = 8;
      ctx.stroke();
  }

  let coord = { x: 0, y: 0 };
  let paint = false;

  function getPosition(event) {
      e = window.event || e;
      var mouse_x = e.clientX || e.touches[0].clientX;
      var mouse_y = e.clientY || e.touches[0].clientY;
      coord.x = mouse_x - canvas.offsetLeft;
      coord.y = mouse_y - canvas.offsetTop;
  }

  function is_it_in_the_circle() {
      var current_radius = Math.sqrt(Math.pow(coord.x - x_orig, 2) + Math.pow(coord.y - y_orig, 2));
      if (radius >= current_radius) return true
      else return false
  }


  function startDrawing(event) {
      paint = true;
      getPosition(event);
      if (is_it_in_the_circle()) {
          ctx.clearRect(0, 0, canvas.width, canvas.height);
          background();
          joystick(coord.x, coord.y);
          Draw();
      }
  }


  function stopDrawing() {
      paint = false;
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      background();
      joystick(width / 2, height / 3);
      document.getElementById("x_coordinate").innerText = 0;
      document.getElementById("y_coordinate").innerText = 0;
      document.getElementById("speed").innerText = 0;
      document.getElementById("angle").innerText = 0;

      send(0,0,0,0);

  }

  function Draw(event) {

    if (paint) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        background();
        var angle_in_degrees,x, y, speed;
        var angle = Math.atan2((coord.y - y_orig), (coord.x - x_orig));

        if (Math.sign(angle) == -1) {
            angle_in_degrees = Math.round(-angle * 180 / Math.PI);
        }
        else {
            angle_in_degrees =Math.round( 360 - angle * 180 / Math.PI);
        }


        if (is_it_in_the_circle()) {
            joystick(coord.x, coord.y);
            x = coord.x;
            y = coord.y;
        }
        else {
            x = radius * Math.cos(angle) + x_orig;
            y = radius * Math.sin(angle) + y_orig;
            joystick(x, y);
        }

    
        getPosition(event);

        var speed =  Math.round(100 * Math.sqrt(Math.pow(x - x_orig, 2) + Math.pow(y - y_orig, 2)) / radius);

        var x_relative = Math.round(x - x_orig);
        var y_relative = Math.round(y - y_orig);
        

        document.getElementById("x_coordinate").innerText =  x_relative;
        document.getElementById("y_coordinate").innerText =y_relative ;
        document.getElementById("speed").innerText = speed;
        document.getElementById("angle").innerText = angle_in_degrees;
        
        //debouncedFunction(x_relative,y_relative,speed,angle_in_degrees);
        const now = +new Date();
        if (now - last > 50){
            last = now;
            send(x_relative,y_relative,speed,angle_in_degrees);
        }
    }
} 