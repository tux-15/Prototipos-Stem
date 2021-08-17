#include <ESP8266WiFi.h>        // WiFi
#include <ESP8266WiFiMulti.h>   // Armazenar credenciais de múltiplas redes e conectar-se na mais forte
#include <ESP8266mDNS.h>        // multi DNS
#include <WebSocketsClient.h>   // WebSocket

ESP8266WiFiMulti wifiMulti;     // Obejto para gerenciar credenciais de rede
WebSocketsClient webSocket; // WebSocket

const int port = 5000;

const byte numChars = 64;       //Número máximo de caracteres por mensagem
char receivedChars[numChars];   //Armazenar mensagem
char tempChars[numChars];       // Array temporário para parsing

char messageFromMC[numChars] = {0};

boolean newData = false;

long previousMillis = 0; 
long interval = 100;  // (em milissegundos) -> define o tempo de "delay"

void startWiFi();
void startMDNS();
void startWebSocket();
void sendMessageWs();


int id = 0;

void setup() {

  Serial.begin(9600);
  delay(500);
  Serial.println('\n');
  
  Serial.println("<ESP ready to accept messages from the Arduino, 0, 0>");
  
  startWiFi();
  startMDNS("stem");
  startWebSocket();


}

void loop() {

  unsigned long currentMillis = millis(); //Usado pelo blink without delay

  //Colocar envio de mensagens aqui
  if(currentMillis - previousMillis > interval) { //Se o tempo especificado tiver passado, executar bloco de código
    previousMillis = currentMillis;
    
    sendMessageWs(messageFromMC);
  }

  recvWithStartEndMarkers();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    newData = false; //Esperar por nova mensagem
  }

  MDNS.update();
  webSocket.loop();
}

void startWiFi(){

  wifiMulti.addAP("LUDUSKAM-2.4G", "ludusKAMt3ch");   // adicionar credenciais das redes
  wifiMulti.addAP("Charlie 2.4", "vox populi");
  wifiMulti.addAP("carreta_stem01", "Cs2k21!!");

  Serial.println("<Connecting>");
  while (wifiMulti.run() != WL_CONNECTED) {  // Esperar WiFi conectar
    delay(250);
  }

  Serial.println("\r\n");
  Serial.print("<Connected to ");
  Serial.println(WiFi.SSID());             // Nome da rede
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Ip do esp na rede local
  Serial.print(">");


  Serial.println("\r\n");

}

void startMDNS(String mdnsName){ // Iniciar o mDNS com o nome desejado para a rede .local

  MDNS.begin(mdnsName); // começa a transmissão do nome
  if (!MDNS.begin(mdnsName)) {
    //Serial.println("Error setting up MDNS responder!");
  }
  Serial.print("<mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local>");

}

void startWebSocket() { // Inicializa o webSocket
  webSocket.begin("192.168.2.105", port, "/");
  
  webSocket.onEvent(webSocketEvent);          // função de callback para eventos que acontecerem no webSocket
  
  Serial.println("<WebSocket server started.>");
}

//void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // Quando alguma mensagem chega pelo webSocket
//  switch (type) {
//    case WStype_DISCONNECTED:             // Se a conexão for interrompida
//      Serial.printf("<[%u] Disconnected!>\n", num);
//      Salva o id da conexão atual
//      id = num;  
//      Serial.println();
//      break;
//    case WStype_CONNECTED: {              // Quando a conexão é estabelecida
//        IPAddress ip = webSocket.remoteIP(num);
//        Serial.printf("<[%u] Connected from %d.%d.%d.%d url: %s>\n", num, ip[0], ip[1], ip[2], ip[3], payload);
//        Serial.println();
//      }
//      break;
//    case WStype_TEXT:                     // Se novos dados forem recebidos
//        Serial.printf("[%u] get Text: %s\n", num, payload);
//        Serial.printf("%s\n", payload);
//        Serial.println();
//        delay(100);
//        break;
//  }
//}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      //Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
    }
      break;
    case WStype_TEXT:
      //Serial.printf("[WSc] get text: %s\n", payload);
      Serial.printf("%s\n", payload);
      Serial.println();

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
        case WStype_PING:
            // pong will be send automatically
            Serial.printf("[WSc] get ping\n");
            break;
        case WStype_PONG:
            // answer to a ping we send
            Serial.printf("[WSc] get pong\n");
            break;
    }

}

void sendMessageWs(const char * payload){
    webSocket.sendTXT(payload);
}

void recvWithStartEndMarkers(){
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // caractere de terminação
                recvInProgress = false;
                ndx = 0;
                strcpy(messageFromMC,receivedChars);
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
