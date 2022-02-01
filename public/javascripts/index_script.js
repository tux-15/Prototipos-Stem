window.setInterval(searchESPs, 1000);

function searchESPs() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      // this.readyState == 4 && this.status == 200
      // esp_list = JSON.parse(this.responseText);
      esp_list = [{ id: "001" }, { id: "002" }, { id: "003" }]; // this line
      let mainDiv = document.getElementById("esps_ativos");
      let htmlContainer = ``;

      if (mainDiv.hasChildNodes()) {
        while (mainDiv.hasChildNodes()) {
          mainDiv.removeChild(mainDiv.firstChild);
        }
        // mainDiv.innerHTML = ``;
      }

      if (esp_list[0] != undefined) {
        esp_list.forEach((esp) => {
          if (esp.taken != true) {
            htmlContainer += `<!-- <div class="description-esp">${esp.id}</div> -->
            <div class="container-monitoring-button">
              <a class="monitoring-button"
              onclick="
                startRobot(${esp.id}, 'monitorador');
              "
              <svg
                  xmlns="http://www.w3.org/2000/svg"
                  width="28.985"
                  height="55"
                  viewBox="0 0 28.985 55"
                >
                  <path
                    class="União_1"
                    data-name="União 1"
                    d="M8.415,53V44.739h4.959V40.36L15.185,38.8a4.114,4.114,0,1,1-.024.454c0-.111,0-.221.013-.33l-1.8,5.817H22v0h1.678V53ZM27.171,28.7a3.978,3.978,0,0,1-7.406-.4,4.18,4.18,0,0,1-.228-1.367,4.012,4.012,0,1,1,8.022,0,4.175,4.175,0,0,1-.387,1.764l-4.11,11.71Zm-7.493-.211-6.511-8.614,6.511,8.614-3.97,8.587Zm0,0,.32.424Zm0,0,.086-.186ZM19.1,14.464a4.187,4.187,0,0,1,.058,4.446,3.957,3.957,0,0,1-5.527,1.306,4.129,4.129,0,0,1-.459-.341,4.175,4.175,0,0,1-.852-5.257h-.071a2.5,2.5,0,0,1-.85-.148l-1.4,1.454-3.5-.125L.586,9.314.763,4.142,3.211,6.52,3.112,9.4,6.6,12.716l2.041.073,1.085-.361a2.691,2.691,0,0,1-.033-.422,2.583,2.583,0,0,1,2.553-2.613,2.512,2.512,0,0,1,.456.042l.382-1.075V6.271L9.971,2.588H7.151L4.915,0H9.971L16.1,6.271V9.853L14.671,11.2a2.687,2.687,0,0,1,.012,1.581,3.919,3.919,0,0,1,3.193.476A4.041,4.041,0,0,1,19.1,14.464l7.5,9.791Z"
                    transform="translate(0.427 1)"
                    fill="none"
                    stroke="#fff"
                    stroke-width="2"
                  />
                </svg>
              <span>Monitoramento</br>ID: ${esp.id}</span>
              </a>
            </div>

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
                <svg
                  xmlns="http://www.w3.org/2000/svg"
                  width="28.985"
                  height="55"
                  viewBox="0 0 28.985 55"
                >
                  <path
                    class="União_1"
                    data-name="União 1"
                    d="M8.415,53V44.739h4.959V40.36L15.185,38.8a4.114,4.114,0,1,1-.024.454c0-.111,0-.221.013-.33l-1.8,5.817H22v0h1.678V53ZM27.171,28.7a3.978,3.978,0,0,1-7.406-.4,4.18,4.18,0,0,1-.228-1.367,4.012,4.012,0,1,1,8.022,0,4.175,4.175,0,0,1-.387,1.764l-4.11,11.71Zm-7.493-.211-6.511-8.614,6.511,8.614-3.97,8.587Zm0,0,.32.424Zm0,0,.086-.186ZM19.1,14.464a4.187,4.187,0,0,1,.058,4.446,3.957,3.957,0,0,1-5.527,1.306,4.129,4.129,0,0,1-.459-.341,4.175,4.175,0,0,1-.852-5.257h-.071a2.5,2.5,0,0,1-.85-.148l-1.4,1.454-3.5-.125L.586,9.314.763,4.142,3.211,6.52,3.112,9.4,6.6,12.716l2.041.073,1.085-.361a2.691,2.691,0,0,1-.033-.422,2.583,2.583,0,0,1,2.553-2.613,2.512,2.512,0,0,1,.456.042l.382-1.075V6.271L9.971,2.588H7.151L4.915,0H9.971L16.1,6.271V9.853L14.671,11.2a2.687,2.687,0,0,1,.012,1.581,3.919,3.919,0,0,1,3.193.476A4.041,4.041,0,0,1,19.1,14.464l7.5,9.791Z"
                    transform="translate(0.427 1)"
                    fill="none"
                    stroke="#fff"
                    stroke-width="2"
                  />
                </svg>
                <span>Braço robótico ID: ${esp.id}</span>
              </a>
              <a
                class="car-button"
                onclick="
                  startRobot(${esp.id}, 'carrinho');
                "
              >
                <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 69.67 30">
                  <path
                    d="M21.17,30A10.59,10.59,0,0,1,11.1,22.48l-.63.07V23.7H.17l-.17-3,7.47-.84V13.5h5.08A10.56,10.56,0,0,1,16.67,10V0h45V9.3A10.5,10.5,0,1,1,48.77,21H31.56a10.52,10.52,0,0,1-10.39,9ZM13.54,19.19l.21,1.43A7.55,7.55,0,0,0,21.17,27h0a7.51,7.51,0,0,0,7.5-7.5V18h23v1.5A7.5,7.5,0,1,0,60,12.05l-1.33-.15V3h-39v9.07l-1,.36a7.44,7.44,0,0,0-4,3.32l-.44.75H10.47v3Z"
                    style="fill: #fff"
                  />
                  <path
                    d="M51.42,19.53l-3-.34c.93-8.31,8.08-10.26,11.71-10.13l-.11,3,.06-1.5-.05,1.5C59.72,12.05,52.27,11.93,51.42,19.53Z"
                    style="fill: #fff"
                  />
                  <path
                    d="M28.81,19.66c-.07-.78-.93-7.53-9.14-7.53h-.34l-.06-3c9.2-.19,12.23,6.64,12.53,10.28l-3,.24,1.49-.12Z"
                    style="fill: #fff"
                  />
                </svg>
                <span>Carrinho </br>ID: ${esp.id}</span>
              </a>
            </div>
            <div class="divisor-esps"></div>`;

            
            // const titleDiv = document.createElement("div");
            // titleDiv.innerText = esp.id;
            // titleDiv.style = "padding-top: 20px;";
            // mainDiv.appendChild(titleDiv);

            // const button1 = document.createElement("button");
            // button1.innerHTML = "Manipulador";
            // button1.onclick = function () {
            //   startRobot(esp.id, "manipulador");
            // };

            // const button2 = document.createElement("button");
            // button2.innerHTML = "Carrinho";
            // button2.onclick = function () {
            //   startRobot(esp.id, "carrinho");
            // };

            // mainDiv.appendChild(button1);
            // mainDiv.appendChild(button2);

            // console.log(mainDiv.innerHTML);
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
