#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include <ArduinoJson.h>

class Utils
{
  private:


  public:
    Utils();
    ~Utils();
    void getJson();
    String meta;
    int passo;
    int estado;
    void setJson(String meta, int passo, int estado);
};
#endif
