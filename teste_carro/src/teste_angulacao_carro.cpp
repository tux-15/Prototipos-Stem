#include <Arduino.h>
#include <AFMotor.h>

//Declarar motores
//Lado direito
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
//Lado esquerdo
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
//Raio da roda
#define raio_roda 0.0325
// Pulsos por revolução do motor
#define ENC_COUNT_REV 341.2
//Lado direito
// Pino de interrupção (Phase A). Rastreia a contagem dos pulsos.
#define ENC_IN_RIGHT_A 19
// Segundo pino digital (Phase B) do encoder. Rastreia o sentido de rotação.
#define ENC_IN_RIGHT_B 47
//Lado Esquerdo
// Pino de interrupção (Phase A). Rastreia a contagem dos pulsos.
#define ENC_IN_LEFT_A 18
// Segundo pino digital (Phase B) do encoder. Rastreia o sentido de rotação.
#define ENC_IN_LEFT_B 50
// True = Frente; False = Trás;
boolean direcao_direita = true;
boolean direcao_esquerda = true;
// Contador de pulsos da roda do lado direito
volatile long pulsos_roda_direita = 0;
// Contador de pulsos da roda do lado direito
volatile long pulsos_roda_esquerda = 0;
// Intervalo de 1 segundo
int intervalo = 500;
// Variáveis para o Blynk Without delay
long previousMillis = 0;
long currentMillis = 0;
// Intervalo de 1 segundo
int intervalo2 = 1000;
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
//=========================================
const byte numChars = 64;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing
// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int mensagemVelocidade = 0;
int mensagemInverte = 0;
boolean newData = false;
//=========================================
int velocidadeD = 0;
int velocidadeE = 0;
bool sentido = false;
//=========================================
void parseData() {      // split the data into its parts
  char copy_receivedChars[sizeof(receivedChars)] = "";
  strcpy(copy_receivedChars, receivedChars);
  char * strtokIndx; // Índice de srttok()
  strtokIndx = strtok(copy_receivedChars, ",");    // Pegar primeira parte (String)
  strcpy(messageFromPC, strtokIndx);      // Armazenar em messageFromPC
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagemVelocidade = atoi(strtokIndx);     // convert this part to an integer
  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float
}
//=========================================
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  while (Serial2.available() > 0 && newData == false) {
    rc = Serial2.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
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
//=========================================
void aguarda_mensagem(){
recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    newData = false;
  }
  //Valores vindo dos sliders
  //Esperando a string 'value0' para a velocidade da roda esquerda
  if (strcmp(messageFromPC, "value0") == 0) {
    velocidadeE = mensagemVelocidade;
  }
  //Esperando a string 'value1' para a velocidade da roda direita
  if (strcmp(messageFromPC, "value1") == 0) {
    velocidadeD = mensagemVelocidade;
  }
  //Valores vindo das caixas de texto
  if (strcmp(messageFromPC, "carrinho") == 0) {
    velocidadeE = mensagemVelocidade;
    velocidadeD = mensagemVelocidade;
  }
  //Valor vindo do botão inverter
  if (strcmp(messageFromPC, "inverter") == 0) {
    sentido = !sentido;
  }
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
void calculo() {
  // Cálcula da velocidade do lado direito
  rpm_direito = (float)(pulsos_roda_direita * 60 / ENC_COUNT_REV);
  w_direito = rpm_direito * rpm_to_radiano;
  velocidade_linear_direita = raio_roda*w_direito; 
  // Cálculo da velocidade do lado esquerdo
  rpm_esquerdo = (float)(pulsos_roda_esquerda * 60 / ENC_COUNT_REV);
  w_esquerdo = rpm_esquerdo * rpm_to_radiano;
  velocidade_linear_esquerda = raio_roda*w_esquerdo;
 /*
 DEBUG
  Serial.print(" Pulsos: ");
  Serial.println(pulsos_roda_direita);
  Serial.print(" RPM: ");
  Serial.print(rpm_direito);
  Serial.println(" RPM");
  Serial.print(" Velocidade Angular: ");
  Serial.print(w_direito);
  Serial.print(" rad/s");
  Serial.print("\t");
  Serial.print(" Velocidade Linear: ");
  Serial.print(velocidade_linear);
  Serial.println(" m/s");
  Serial.println();
  */
  pulsos_roda_direita = 0;
  pulsos_roda_esquerda = 0;
}
//=========================================
void controle() {
  //Frente
  if (sentido == true) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
  //Trás
  else if (sentido == false) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }
  //Parar
  if (velocidadeD < 90 && velocidadeE < 90) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    velocidadeD = 0;
    velocidadeE = 0;
  }
  //Lado Direito
  motor1.setSpeed(velocidadeD);
  motor2.setSpeed(velocidadeD);
  //Lado Esquerdo
  motor3.setSpeed(velocidadeE);
  motor4.setSpeed(velocidadeE);
}
//=========================================
void setup() {
  // Define os pinos do encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
  pinMode(ENC_IN_LEFT_A, INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B, INPUT);
  // Abre a porta serial 1 com BAUDRATE=9600
  Serial.begin(9600);
  // Abre a porta serial 2 com BAUDRATE=9600
  Serial2.begin(9600);
  // Funções de interrupção externa
attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), roda_direita_contador, RISING);
attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), roda_esquerda_contador, RISING);
}
//=========================================
void loop() {
   controle();
  // Resgitra o tempo de envio de informações
  currentMillis = millis();
  // Resgitra o tempo de cálculo da velocidade
  currentMillis2 = millis();
  // Depois de um segundo, mostra-se o número de pulsos.
  if (currentMillis - previousMillis > intervalo) {
    previousMillis = currentMillis;
    Serial2.print("<rpm,");Serial2.print(rpm_direito);Serial2.print(",0>");
    //Serial.print("I got: "); Serial.print(mensagemVelocidadeE); Serial.println();
  }
    if (currentMillis2 - previousMillis2 > intervalo2) {
    previousMillis2 = currentMillis2;
    calculo();
  }
  //função que recebe e atribui as mensagens às variáveis de velocidade
  aguarda_mensagem();
}