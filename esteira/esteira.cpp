#include "esteira.h"

Esteira::Esteira(){
  pinMode (this->stepPin, OUTPUT);
  pinMode (this->dirPin, OUTPUT);
  this->power = false;
};

Esteira::~Esteira(){};

void Esteira::Run(int meioPeriodo, boolean direcao){
  if(this->power == true){
    
    digitalWrite(this->dirPin,direcao);

    digitalWrite(this->stepPin,HIGH);
    delayMicroseconds(meioPeriodo);
    digitalWrite(this->stepPin,LOW);
    delayMicroseconds(meioPeriodo);
  }
};
