#include <Arduino.h>
#include <AFMotor.h>

//Raio da roda
#define raio_roda 0.0325
// Pulsos por revolução do motor
#define ENC_COUNT_REV 341.2

// Pino de interrupção (Phase A). Rastreia a contagem dos pulsos.
#define ENC_IN_RIGHT_A 19

// Segundo pino digital (Phase B) do encoder. Rastreia o sentido de rotação.
#define ENC_IN_RIGHT_B 52

// Pino de interrupção (Phase A). Rastreia a contagem dos pulsos.
#define ENC_IN_LEFT_A 18
// Segundo pino digital (Phase B) do encoder. Rastreia o sentido de rotação.
#define ENC_IN_LEFT_B 50

//Declarar motores
AF_DCMotor motor1(1);
AF_DCMotor motor3(3);

#define Pot A8
#define buzzer 22


boolean buzzer_estado = false;
// True = Frente; False = Trás;
boolean direcao_direita = true;
boolean direcao_esquerda = true;
// Contador de pulsos da roda do lado direito
volatile long pulsos_roda_direita = 0;
// Contador de pulsos da roda do lado direito
volatile long pulsos_roda_esquerda = 0;
// Intervalo de 1 segundo
int intervalo = 1000;
// Intervalo de 2 segundo
int intervalo2 = 2000;
// Variáveis para o Blynk Without delay
long previousMillis = 0;
long currentMillis = 0;
// Variáveis para o Blynk Without delay
long previousMillis2 = 0;
long currentMillis2 = 0;
//Variáveis para o cálculo da velocidade
// Variáveis para medir o RPM da roda direita
float rpm_direito = 0;
// Variáveis para medir o RPM da roda direita
float rpm_esquerdo = 0;
// Variável para medir a velocidade angular da roda direita
float w_direito = 0;
// Variável para medir a velocidade angular da roda esquerda
float w_esquerdo = 0;
// Variáveis para medir a velocidade linear
float velocidade_linear_direita = 0;
float velocidade_linear_esquerda = 0;
// Constante para converter rpm em radiano
const float rpm_to_radiano = 0.10471975512;

int pot = 0;
int velocidade_pot = 0;
float velocidade_linear = 0;

void controle() {
  pot = analogRead(Pot);
  velocidade_pot = map(pot, 0, 1023, 0, 255);
/*
  motor1.run(FORWARD);
  motor3.run(FORWARD);
*/
  motor1.run(BACKWARD);
  motor3.run(BACKWARD);
  
  motor1.setSpeed(velocidade_pot);
  motor3.setSpeed(velocidade_pot);
}

//=========================================
void roda_direita_contador() {
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
//=========================================
void roda_esquerda_contador() {
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
//=========================================
//=========================================
void calculo() {
  // Cálcula da velocidade do lado direito
  rpm_direito = (float)(pulsos_roda_direita * 60 / ENC_COUNT_REV);
  w_direito = rpm_direito * rpm_to_radiano;
  velocidade_linear_direita = raio_roda*w_direito; 
  // Cálculo da velocidade do lado esquerdo
  rpm_esquerdo = (float)(pulsos_roda_esquerda * 60 / ENC_COUNT_REV);
  w_esquerdo = rpm_esquerdo * rpm_to_radiano;
  velocidade_linear_esquerda = raio_roda*w_esquerdo;

  Serial.print(" Pulsos Direito: ");
  Serial.println(pulsos_roda_direita);
  Serial.print(" RPM Direito: ");
  Serial.print(rpm_direito);
  Serial.println(" RPM");
  Serial.print(" Velocidade Angular Direito: ");
  Serial.print(w_direito);
  Serial.print(" rad/s");
  Serial.print("\t");
  Serial.print(" Velocidade Linear Direito: ");
  Serial.print(velocidade_linear_direita);
  Serial.println(" m/s");
  Serial.print(" Pulsos Esquerdo: ");
  Serial.println(pulsos_roda_esquerda);
  Serial.print(" RPM Esquerdo: ");
  Serial.print(rpm_esquerdo);
  Serial.println(" RPM");
  Serial.print(" Velocidade Angular Esquerdo: ");
  Serial.print(w_esquerdo);
  Serial.print(" rad/s");
  Serial.print("\t");
  Serial.print(" Velocidade Linear Esquerdo: ");
  Serial.print(velocidade_linear_esquerda);
  Serial.println(" m/s");
  Serial.println();
  pulsos_roda_direita = 0;
  pulsos_roda_esquerda = 0;
}
//=========================================

void setup() {

  // Abre a porta serial com BAUDRATE=9600
  Serial.begin(9600);

  // Define os pinos do encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
  pinMode(ENC_IN_LEFT_A, INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B, INPUT);
  pinMode(buzzer, OUTPUT);
  // Cada vez que o pino fica alto, isto é um pulso
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), roda_direita_contador, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), roda_esquerda_contador, RISING);
}

void loop() {
  controle();
  // Resgitra o tempo
  currentMillis = millis();
  currentMillis2 = millis();
  // Depois de um segundo, mostra-se o número de pulsos.
  if (currentMillis - previousMillis > intervalo) {
    previousMillis = currentMillis;
    calculo();
  }
  // Depois de dois segundos, toca o buzzer.
  if (currentMillis2 - previousMillis2 > intervalo2) {
    previousMillis2 = currentMillis2;
    buzzer_estado = !buzzer_estado;
  }
  digitalWrite(buzzer, buzzer_estado);
}

