#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266mDNS.h>        // Include the mDNS library
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include <WebSocketsServer.h>
#include <FS.h>   // Include the SPIFFS library

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80
WebSocketsServer webSocket(81);   // create a websocket server on port 81

// function prototypes

void startWiFi();
void startMDNS();
void startServer();

String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);       // send the right file to the client (if it exists)


void handleRoot();             
void handleNotFound();

void handleCar();
void handleServo();

//---------------------------

void setup() {

  
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(500);
  Serial.println('\n');
  SPIFFS.begin(); 

  startWiFi();
  startMDNS("roboSTEM");
  startWebSocket();            // Start a WebSocket server
  startServer();
  
}

void loop() {
  MDNS.update();
  server.handleClient();                    // Listen for HTTP requests from clients
  webSocket.loop(); 

}

void startWiFi(){
  
  wifiMulti.addAP("LUDUSKAM-2.4G", "ludusKAMt3ch");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Charlie 2.4", "vox populi");
  wifiMulti.addAP("carreta-stem-01", "Stem2021!!");

  Serial.println("<Connecting, 1, 2>");
  while (wifiMulti.run() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print("<.>");
  }
  
  Serial.println("\r\n");
  Serial.print("<Connected to >");
  Serial.println(WiFi.SSID());             // Tell us what network we're connected to
  Serial.print("<IP address:\t");
  Serial.print(WiFi.localIP()); Serial.print(">");            // Send the IP address of the ESP8266 to the computer
  
  
  Serial.println("\r\n");

}

void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("<WebSocket server started.>");
}

void startMDNS(String mdnsName){ // Start the mDNS responder
  
  MDNS.begin(mdnsName); // start the multicast domain name server                      
  if (!MDNS.begin(mdnsName)) {             // Start the mDNS responder for esp8266.local
    //Serial.println("Error setting up MDNS responder!");
  }
  Serial.print("<mDNS responder started: http://>");
  Serial.print(mdnsName);
  Serial.println("<.local>");
  
}

void startServer(){ // Start a HTTP server with a file read handler and an upload handler

  server.onNotFound([]() {                              // If the client requests any URI
  if (!handleFileRead(server.uri()))                  // send it if it exists
    server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  server.begin();                           // Actually start the server
  Serial.println("<HTTP server started>");
  
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("<[%u] Disconnected!>\n", num);
      Serial.println();
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("<[%u] Connected from %d.%d.%d.%d url: %s>\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        Serial.println();
      }
      break;
    case WStype_TEXT:                     // if new text data is received
        //Serial.printf("[%u] get Text: %s\n", num, payload);
        Serial.printf("%s\n", payload);
        Serial.println();
        delay(100);
        break;
  }
}

String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){  // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";           // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){  // If the file exists, either as a compressed archive, or normal
    if(SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
      path += ".gz";                                         // Use the compressed version
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);
  return false;                                          // If the file doesn't exist, return false
} 
