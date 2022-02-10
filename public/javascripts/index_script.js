window.setInterval(searchESPs, 1000);

function searchESPs() {
  const xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      // esp_list = JSON.parse(this.responseText);
      esp_list = [
        { id: "001", type: "manual" },
        { id: "002", type: "manual" },
        { id: "003", type: "sistema" },
      ]; // this line

      const mainDiv = document.getElementById("esps_ativos");
      let htmlContainer = ``;

      if (mainDiv.hasChildNodes()) {
        while (mainDiv.hasChildNodes()) {
          mainDiv.removeChild(mainDiv.firstChild);
        }
        // mainDiv.innerHTML = ``;
      }

      if (esp_list.length > 0) {
        const systemEsp = esp_list.find((esp) => esp.type === "sistema");

        if (systemEsp) {
          htmlContainer += 
          `<div class="container-monitoring-button">
            <a class="monitoring-button"
              onclick="
              startRobot(${systemEsp.id}, 'dashboard');
              "
            >
              <span>Monitoramento</br>ID: ${systemEsp.id}</span>
            </a>
          </div>`;
        }

        esp_list.forEach((esp) => {
          if (!esp.taken) {
            htmlContainer += `
              <div class="container-img">
                <img src="./images/index/robot-arm.png" class="robot-img">
                <img src="./images/carrinho/Chassi_II.png" class="car-img">
              </div>
              
              <div class="container-arm-car-button">
                <a
                  class="arm-button"
                  onclick="
                    startRobot(${esp.id}, 'manipulador');
                  "
                >
                <img src="./images/index/robotic-arm.svg" />
                  <span>Braço robótico ID: ${esp.id}</span>
                </a>
                <a
                  class="car-button"
                  onclick="
                    startRobot(${esp.id}, 'carrinho');
                  "
                >
                  <img src="./images/index/car.svg" />
                  <span>Carrinho </br>ID: ${esp.id}</span>
                </a>
              </div>
              <div class="divisor-esps"></div>`;
          }
        });

        mainDiv.innerHTML = htmlContainer;
      }
    }
  };
  xhttp.open("GET", "/getESPs", true);
  xhttp.send();
}

function startRobot(esp_id, robot) {
  console.log("start");
  document.cookie = "esp_id" + "=" + esp_id;
  document.cookie = "robot" + "=" + robot;
  location.href = "/" + robot;
}
