#include <ESP8266WiFi.h>        // WiFi
#include <ESP8266WiFiMulti.h>   // Armazenar credenciais de múltiplas redes e conectar-se na mais forte
#include <ESP8266mDNS.h>        // multi DNS
#include <WiFiClient.h>         // WiFi softAP
#include <ESP8266WebServer.h>   // HTTP
#include <WebSocketsServer.h>   // WebSocket
#include <FS.h>                 // Sistema de arquivos SPIFFS


ESP8266WiFiMulti wifiMulti;     // Obejto para gerenciar credenciais de rede

ESP8266WebServer server(80);    // Webserver para utilização do protocolo HTTP na porta 80
WebSocketsServer webSocket(81); // WebSocket na porta 81

//====================================================================

//variaveis para comunicação no sentindo arduino -> ESP

const byte numChars = 64;       //Número máxim de caracteres por mensagem
char receivedChars[numChars];   //Armazenar mensagem
char tempChars[numChars];       // Array temporário para parsing


// Armazenar mensagem depois do parsing

//messageFromMC (micro controller) para diferenciar da messageFromPC no código do arduino

char messageFromMC[numChars] = {0};
int integerFromMC = 0;
int integerFromMC2 = 0;

//Adicionar mais conforme necessidade
//float floatFromMC = 0.0;

boolean newData = false;

//====================================================================

// Protótipo das funções

void startWiFi();
void startMDNS();
void startServer();
void sendMessageWs();

// id da conexão atual -> é atualizado no callback do websocket (on event)
int id = 0;

String getContentType(String filename);
bool handleFileRead(String path);

//---------------------------

void setup() {


  Serial.begin(9600);
  delay(500);
  Serial.println('\n');
  SPIFFS.begin(); // Inicializa o SPI file system

  /*
    Inicializa os serviços:
      -Conexão WiFi
      -O gerenciador de multi DNS
      -O webSocket
      -O servidor http
  */

  //Serial.print("<");
  Serial.println("<ESP ready to accept messages from the Arduino>");
  startWiFi();
  startMDNS("stem");
  startWebSocket();
  startServer();
  //Serial.print(">");

}

void loop() {
  //Keep-alive do MDNS, servidor e webSocket
  MDNS.update();
  server.handleClient();
  webSocket.loop();
 
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
//    int sum = integerFromPC + integerFromPC2;
//    char a [33];
//    itoa(sum, a, 16);
    sendMessageWs(id, "Something came");
    //Serial.println("<Arduino diz:>");
    newData = false; //Esperar por nova mensagem
  }
}

void startWiFi(){

  wifiMulti.addAP("LUDUSKAM-2.4G", "ludusKAMt3ch");   // adicionar credenciais das redes
  wifiMulti.addAP("Charlie 2.4", "vox populi");
  wifiMulti.addAP("carreta-stem-01", "Stem2021!!");

  Serial.println("<Connecting>");
  while (wifiMulti.run() != WL_CONNECTED) {  // Esperar WiFi conectar
    delay(250);
    Serial.print("<.>");
  }

  Serial.println("\r\n");
  Serial.print("<Connected to ");
  Serial.println(WiFi.SSID());             // Nome da rede
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Ip do esp na rede local
  Serial.print(">");


  Serial.println("\r\n");

}

void startWebSocket() { // Inicializa o webSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);          // função de callback para eventos que acontecerem no webSocket
  Serial.println("<WebSocket server started.>");
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

void startServer(){ // Inicia o servidor com um File Read Handler e um upload handler

  server.onNotFound([]() {                              // Caso o client requisiste um arquivo
  if (!handleFileRead(server.uri()))                    // Mandar se existir
    server.send(404, "text/plain", "404: Not Found");   // Retornar 404 se não existir
  });
  server.begin();                                       // Inicia o servidor
  Serial.println("<HTTP server started>");

}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // Quando alguma mensagem chega pelo webSocket
  switch (type) {
    case WStype_DISCONNECTED:             // Se a conexão for interrompida
      Serial.printf("<[%u] Disconnected!>\n", num);
      //Salva o id da conexão atual
      id = num;
      Serial.println();
      break;
    case WStype_CONNECTED: {              // Quando a conexão é estabelecida
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("<[%u] Connected from %d.%d.%d.%d url: %s>\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        Serial.println();
      }
      break;
    case WStype_TEXT:                     // Se novos dados forem recebidos
        //Serial.printf("[%u] get Text: %s\n", num, payload);
        Serial.printf("%s\n", payload);
        Serial.println();
        delay(100);
        break;
  }
}

void sendMessageWs(uint8_t id, const char * payload){
    webSocket.sendTXT(id, payload);
}

String getContentType(String filename) { // Converter o arquivo para MIME
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".svg")) return "image/svg+xml";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){  // Serve o arquivo correto para o client (se existir)
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";           // Mandar o index.html para "/"
  String contentType = getContentType(path);             // achar o arquivo MIME
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){  // Checa se o arquivo existe tanto normal como compressado (.gzip)
    if(SPIFFS.exists(pathWithGz))                        // Se houver uma versão compressada, usar
      path += ".gz";                                     // Use the compressed version
    File file = SPIFFS.open(path, "r");                  // Abrir arquivo
    size_t sent = server.streamFile(file, contentType);  // mandar para o client
    file.close();                                        // Fechar arquivo
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);
  return false;                                          // Se o arquivo não existir retornar false

}

//=========================================================================================================

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
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//=================================================================

void parseData() {      // Dividir a mensagem em partes

    char * strtokIndx; // Índice de srttok()

    strtokIndx = strtok(tempChars,",");     // Pegar primeira parte (String)
    strcpy(messageFromMC, strtokIndx);      // Armazenar em messageFromPC 
 
    strtokIndx = strtok(NULL, ",");         // Continuar a dividir a mensagem
    integerFromMC = atoi(strtokIndx);       // Converte para interiro e armazena na variável

    strtokIndx = strtok(NULL, ",");         // Repete a operação anterior
    integerFromMC2 = atoi(strtokIndx);      // Repetir para quantas partes forem necessárias

    // strtokIndx = strtok(NULL, ",");
    // floatFromPC = atof(strtokIndx);      // Caso seja necessário receber um float

}
