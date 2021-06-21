#include <AFMotor.h>

#define    encoder_C1   2                     //Conexão C1 do encoder
#define    encoder_C2   24                     //Conexão C2 do encoder
#define    encoder_C3   3                    //Conexão C1 do encoder
#define    encoder_C4   28                     //Conexão C2 do encoder

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int mensagem_velocidade = 0;
int mensagem_angulo = 0;

float floatFromPC = 0.0;

boolean newData = false;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int velocidade = 0;
int angulo = 0;
long velocidadeA = 0;
long velocidadeB = 0;
int Xdif = 0;

byte      Encoder_C1Last;
float rpm = 0;
int pulse_number1;
boolean direction_m;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial2.println("O arduino espera uma mensagem do tipo <String, int, int>");
  Serial2.println();
  Serial.println("O arduino espera uma mensagem do tipo <String, int, int>");
  attachInterrupt(0, contador_pulsos, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }

  if (strcmp(messageFromPC, "carrinho") == 0) {
    velocidade = mensagem_velocidade;
    angulo = mensagem_angulo;
  }
  //calculo();
  controle();
  pulse_number1 = 0;
}

void controle() {

  //Frente
  if (angulo > 80 and angulo < 100) {

    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    velocidadeA = map(velocidade, 0, 100, 0, 255);
    velocidadeB = map(velocidade, 0, 100, 0, 255) + 20;
  }

  //Trás
  else if (angulo > 260 and angulo < 280) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);

    velocidadeA = map(velocidade, 0, 100, 0, 255);
    velocidadeB = map(velocidade, 0, 100, 0, 255) + 20;
  }

  //Esquerda
  else if (angulo > 170 and angulo < 190) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    Xdif = map(velocidade, 0, 100, 0, 150);
    velocidadeA = 150 + Xdif;
    velocidadeB = 160 - Xdif * 0.75;


  }

  //Direita
  else if (angulo > 340 and angulo < 360) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    Xdif = map(velocidade, 0, 100, 0, 150);
    velocidadeA = 150 - Xdif * 0.75;
    velocidadeB = 160 + Xdif;
  }

  //Parar
  else if (velocidade < 20) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);

    velocidadeA = 0;
    velocidadeB = 0;
  }

if (velocidadeA > 255) {
    velocidadeA = 255;
  }

  if (velocidadeB > 255) {
    velocidadeB = 255;
  }

  if (velocidadeA < 0) {
    velocidadeA = 0;
  }

  if (velocidadeB < 0) {
    velocidadeB = 0;
  }

  //Mudança de velocidade
  motor1.setSpeed(velocidadeA);
  motor2.setSpeed(velocidadeA);
  motor3.setSpeed(velocidadeB);
  motor4.setSpeed(velocidadeB);

}

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

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagem_velocidade = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagem_angulo = atoi(strtokIndx);     // convert this part to an integer

  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
  Serial.print("Robô: ");
  Serial.println(messageFromPC);
  Serial.print("Velocidade: ");
  Serial.println(velocidade);
  Serial.print("Ângulo: ");
  Serial.println(angulo);
}


void contador_pulsos()
{
  int Lstate = digitalRead(encoder_C1);       //Lê estado de encoder_C1 e armazena em Lstate

  if (!Encoder_C1Last && Lstate)              //Encoder_C1Last igual a zero e Lstate diferente de zero?
  { //Sim...
    int val = digitalRead(encoder_C2);        //Lê estado de encoder_C2 e armazena em val

    if (!val && direction_m) direction_m = false;     //Sentido reverso

    else if (val && !direction_m) direction_m = true; //Sentido direto

  } //end if

  Encoder_C1Last = Lstate;                    //Encoder_C1Last recebe o valor antigo
  if (!direction_m) pulse_number1++;
  else              pulse_number1--;
}

void calculo() {
  Serial.print("Num. Pulsos: ");              //Imprime
  Serial.println(pulse_number1);
  rpm = (pulse_number1 / 341.2) * 300;
  Serial.print(" Rpm: ");              //Imprime
  Serial.print(rpm);
}
