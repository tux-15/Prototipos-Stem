#include "Wifi.h"

WifiManager::WifiManager(){ //Constructor
  wifiMulti.addAP("LUDUSKAM-2.4G", "ludusKAMt3ch");   // adicionar credenciais das redes
  wifiMulti.addAP("Charlie 2.4", "vox populi");
  wifiMulti.addAP("STEMLABNET", "1n0v@c@02021");
};

WifiManager::~WifiManager(){ /* ¯\_(ツ)_/¯ */}; //Destructor

void WifiManager::startWiFi(){

  Serial.println("\n\rConnecting");
  while (wifiMulti.run() != WL_CONNECTED) {  // Esperar WiFi conectar
    delay(250);
    Serial.print(".");
  };

  Serial.print("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             // Nome da rede
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Ip do esp na rede local

  Serial.println("\r\n");
};

void WifiManager::startMDNS(String mdnsName){ // Iniciar o mDNS com o nome desejado para a rede .local

  MDNS.begin(mdnsName); // começa a transmissão do nome
  if (!MDNS.begin(mdnsName)) {
    //Serial.println("Error setting up MDNS responder!");
  }
  Serial.print("mDNS responder started: http://"); 
  Serial.print(mdnsName); Serial.println(".local");

};

void WifiManager::updateMDNS(){
  MDNS.update();
};
