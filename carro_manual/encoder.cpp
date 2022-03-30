#include "encoder.h"
#include "serial_comm.h"

Serial_comm serial_velocidade;

#define ENC_COUNT_REV 375
#define ENC_IN_RIGHT_A 18
//#define ENC_IN_RIGHT_A 20
#define ENC_IN_RIGHT_B  22
#define ENC_IN_LEFT_A 19
//#define ENC_IN_LEFT_A 21
#define ENC_IN_LEFT_B 24

boolean direcao_direita = true;
boolean direcao_esquerda = true;

volatile long pulsos_roda_direita = 0;
volatile long pulsos_roda_esquerda = 0;

long previousMillis = 0;
long intervalo = 250;
    
float rpm_direito = 0;
float rpm_esquerdo = 0;
float rpm = 0;

void setEncoder(){
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
  pinMode(ENC_IN_LEFT_A, INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), roda_direita_contador, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), roda_esquerda_contador, RISING);
}

void calculoVelocidade() {

  long currentMillis = millis();

  if (currentMillis - previousMillis >= intervalo) {
    previousMillis = currentMillis;
    rpm_direito = (float)(pulsos_roda_direita*60*4/ENC_COUNT_REV);
    rpm_esquerdo = (float)(pulsos_roda_esquerda *4*60 / ENC_COUNT_REV);
    rpm = (rpm_direito+rpm_esquerdo)/2;
    serial_velocidade.sendJson("carSpeed", String(rpm));
    
    pulsos_roda_direita = 0;
    pulsos_roda_esquerda = 0;
  }
    
//    Serial.print(" Numero de pulsos: ");
//    Serial.print(pulsos_roda_direita);
//    Serial.print(" RPM Direito: ");
//    Serial.println(rpm_direito);

}

void roda_direita_contador(){
  // Lê o valor do encoder da roda direita
  int val = digitalRead(ENC_IN_RIGHT_B);

  if (val == LOW) {
    direcao_direita = false; // Trás
  }
  else {
    direcao_direita = true; // Frente
  }

  if (direcao_direita) {
    pulsos_roda_direita++;
  }
  else {
    pulsos_roda_direita--;
  }
}

void roda_esquerda_contador(){
  // Lê o valor do encoder da roda direita
  int val = digitalRead(ENC_IN_LEFT_B);

  if (val == LOW) {
    direcao_esquerda = false; // Trás
  }
  else {
    direcao_esquerda = true; // Frente
  }

  if (direcao_esquerda) {
    pulsos_roda_esquerda++;
  }
  else {
    pulsos_roda_esquerda--;
  }
}
