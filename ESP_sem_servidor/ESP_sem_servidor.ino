#include <ESP8266WiFi.h>        // WiFi
#include <ESP8266WiFiMulti.h>   // Armazenar credenciais de múltiplas redes e conectar-se na mais forte
#include <WebSocketsClient.h>   // WebSocket

ESP8266WiFiMulti wifiMulti;     // Obejto para gerenciar credenciais de rede
WebSocketsClient webSocket; // WebSocket

const int port = 1801;
const char * ip = "192.168.2.105";

long previousMillis = 0; 
long interval = 500;  // (em milissegundos) -> define o tempo de "delay"

void startWiFi();
void startWebSocket();
void sendMessageWs();

void setup() {

  delay(100);
  Serial.begin(9600);
  delay(250);
  
  Serial.println("\n\rESP ready");
  
  //startWiFi();
  //startWebSocket();

}

void loop() {

  //getJson();

  unsigned long currentMillis = millis(); //Usado pelo blink without delay

  //Colocar envio de mensagens aqui
  if(currentMillis - previousMillis > interval) { //Se o tempo especificado tiver passado, executar bloco de código

    long intervalo = currentMillis - previousMillis;
    previousMillis = currentMillis;
    //sendMessageWs();
  }

  //webSocket.loop();
}

void startWiFi(){

  wifiMulti.addAP("LUDUSKAM-2.4G", "ludusKAMt3ch");   // adicionar credenciais das redes
  wifiMulti.addAP("Charlie 2.4", "vox populi");
  wifiMulti.addAP("carreta_stem01", "Cs2k21!!");
  wifiMulti.addAP("MUSTAFA_2.4G", "96143008");
  wifiMulti.addAP("Seixas_Net", "Mayum647");
  wifiMulti.addAP("Tux", "1234abcd");
  


  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED) {  // Esperar WiFi conectar
    delay(250);
  }

  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             // Nome da rede
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Ip do esp na rede local
  Serial.println("\r\n");
}

void startWebSocket() { // Inicializa o webSocket
  webSocket.begin(ip, port, "/");
  webSocket.onEvent(webSocketEvent);          // função de callback para eventos que acontecerem no webSocket
  
  Serial.println("WebSocket client started.");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  
  switch(type) {    
    case WStype_DISCONNECTED: 
      Serial.printf("\rDisconnected!\n");
      break;
    
    case WStype_CONNECTED: 
      Serial.printf("\rConnected to url: %s\n\r", payload);

      // send message to server when Connected
      webSocket.sendTXT("{\"start\": \"ESP_on\"}");
      break;
      
    case WStype_TEXT:
      Serial.printf("%s", payload);
      Serial.println();

      break;
    case WStype_BIN:
      hexdump(payload, length);
      Serial.println();
      break;
        
    case WStype_PING:
      // pong will be send automatically
      //Serial.printf("\r[WSc] get ping\n\r");
      break;
      
    case WStype_PONG:
      // answer to a ping we send
      //Serial.printf("\r[WSc] get pong\n");
      break;       
  }
}

void sendMessageWs(String& payload){//const char * payload){
    webSocket.sendTXT(payload);
}
