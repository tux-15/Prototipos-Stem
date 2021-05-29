#include <AFMotor.h>

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

String botao = "";
boolean state = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial2.println("O arduino espera uma mensagem do tipo <String, int, int>");
  Serial2.println();
  Serial.println("O arduino espera uma mensagem do tipo <String, int, int>");

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
  /*
      if(botao == "ok"){
          state != state;
      }
  */

  if (strcmp(messageFromPC, "carrinho") == 0) {
    velocidade = mensagem_velocidade;
    angulo = mensagem_angulo;
  }
  controle();
}

void controle() {

  //Frente
  if (angulo > 80 and angulo < 100) {

    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    velocidadeA = map(velocidade, 20, 100, 0, 255);
    velocidadeB = map(velocidade, 20, 100, 0, 255);

    motor1.setSpeed(velocidadeA);
    motor2.setSpeed(velocidadeB);
    motor3.setSpeed(velocidadeA);
    motor4.setSpeed(velocidadeB);
  }

  //Trás
  else if (angulo > 260 and angulo < 280) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);

    velocidadeA = map(velocidade, 20, 100, 0, 255);
    velocidadeB = map(velocidade, 20, 100, 0, 255);
  }

  //Esquerda
  else if (angulo > 170 and angulo < 190) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    Xdif = map(velocidade, 0, 100, 0, 255);
    velocidadeA = 150;
    velocidadeB = Xdif;


  }

  //Direita
  else if (angulo > 350 and angulo < 10) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    Xdif = map(velocidade, 0, 100, 0, 255);
    velocidadeA = Xdif;
    velocidadeB = 170;
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

  //Mudança de velocidade
  motor1.setSpeed(velocidadeA);
  motor2.setSpeed(velocidadeB);
  motor3.setSpeed(velocidadeA);
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
  Serial.print("VelocidadeA: ");
  Serial.println(velocidadeA);
  Serial.print("VelocidadeB: ");
  Serial.println(velocidadeB);
}
