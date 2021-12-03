
window.setInterval(searchESPs, 1000);

function searchESPs() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            esp_list = JSON.parse(this.responseText);
            //esp_list = [{"id":"001"}, {"id":"002"}, {"id":"003"}];
            const mainDiv = document.getElementById("esps_ativos");

            if(mainDiv.hasChildNodes()){
                while (mainDiv.hasChildNodes()) {  
                    mainDiv.removeChild(mainDiv.firstChild);
                }; 
            };

            if(esp_list[0] != undefined){
                esp_list.forEach(esp => {
                    if(esp.taken != true){
                        const titleDiv = document.createElement("div");
                        titleDiv.innerText = esp.id;
                        titleDiv.style = "padding-top: 20px;";
                        mainDiv.appendChild(titleDiv);

                        const button1 = document.createElement("button");
                        button1.innerHTML = "Manipulador";
                        button1.onclick =  function() {startRobot(esp.id, 'manipulador')};

                        const button2 = document.createElement("button");
                        button2.innerHTML = "Carrinho";
                        button2.onclick =  function() {startRobot(esp.id, 'carrinho')};

                        mainDiv.appendChild(button1);
                        mainDiv.appendChild(button2);
                    };
                });
            };
        };
    };
    xhttp.open("GET", "/getESPs", true);
    xhttp.send();
};

function startRobot(esp_id, robot){
    document.cookie = "esp_id" + "=" + esp_id;
    document.cookie = "robot" + "=" + robot;
    location.href = "/" + robot;
};  