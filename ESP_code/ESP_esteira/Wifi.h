#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>        // WiFi
#include <ESP8266mDNS.h>        // multi DNS
#include <ESP8266WiFiMulti.h>


class WifiManager {

  private:
    
    ESP8266WiFiMulti wifiMulti;     // Obejto para gerenciar credenciais de rede
    
  public:
    WifiManager(); //Constructor
    ~WifiManager();

    String ip = "";
    void startWiFi();
    void startMDNS(String mdnsName);
    void updateMDNS();
};

#endif
