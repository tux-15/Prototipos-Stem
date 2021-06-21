#include <AFMotor.h>

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
<<<<<<< HEAD
int mensagemVelocidadeE = 0;
int mensagemVelocidadeD = 0;
int mensagemInverte = 0;
=======
int mensagemVelocidadeL = 0;
int mensagemVelocidadeD = 0;
int mensagemPower = 0;
int mensagemSentido = 0;
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
//float floatFromPC = 0.0;

boolean newData = false;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

<<<<<<< HEAD
int velocidadeD = 0;
int velocidadeE = 0;
bool sentido = false;
=======
int velocidadeR = 0;
int velocidadeL = 0;
int velocidadeA = 0;
int velocidadeB = 0;
int power = 0;
int sentido = 0;
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac

//============

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial2.println("O arduino espera uma mensagem do tipo <String, int, int>");
}

//============

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

<<<<<<< HEAD
//Valores vindo dos sliders
  //Esperando a string 'value0' para a velocidade da roda esquerda
  if (strcmp(messageFromPC, "value0") == 0) {
    velocidadeE = mensagemVelocidadeE;
  }

  //Esperando a string 'value1' para a velocidade da roda direita
  if (strcmp(messageFromPC, "value1") == 0) {
    velocidadeD = mensagemVelocidadeD;
  }

//Valores vindo das caixas de texto
  if (strcmp(messageFromPC, "carrinho") == 0) {
    velocidadeE = mensagemVelocidadeE;
    velocidadeD = mensagemVelocidadeD;
  }

//Valor vindo do botão inverter
  if (strcmp(messageFromPC, "inverter") == 0) {
    sentido = !sentido;
  }

  controle();
=======
  if (strcmp(messageFromPC, "carrinho") == 0) {
    power = mensagemPower;
    sentido = mensagemSentido;
    velocidadeR = mensagemVelocidadeD;
    velocidadeL = mensagemVelocidadeL;
  }

  if (power == 1) {
    Serial2.println("Carro Ligado!");
    controle();
  }

  else {
    Serial2.println("Carro desligado!");
  }
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac

}

//============

void controle() {
<<<<<<< HEAD
  
  //Frente
  if (sentido == true) {
=======
  //Frente
  if (sentido == 1) {
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
<<<<<<< HEAD
  }

  //Trás
  else if (sentido == false) {
=======

    velocidadeA = map(velocidadeR, 0, 100, 0, 255);
    velocidadeB = map(velocidadeL, 0, 100, 0, 255);
  }

  //Trás
  else if (sentido == 2) {
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
<<<<<<< HEAD
  }

  //Parar
  if (velocidadeD < 90 && velocidadeE < 90) {
=======

    velocidadeA = map(velocidadeR, 0, 100, 0, 255);
    velocidadeB = map(velocidadeL, 0, 100, 0, 255);
  }

  //Parar
  if (velocidadeR < 20 && velocidadeL < 20) {
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
<<<<<<< HEAD
    velocidadeD = 0;
    velocidadeE = 0;
  }

  //Lado Direito
  motor1.setSpeed(velocidadeD);
  motor2.setSpeed(velocidadeD);
  //Lado Esquerdo
  motor3.setSpeed(velocidadeE);
  motor4.setSpeed(velocidadeE);
=======
    velocidadeA = 0;
    velocidadeB = 0;
  }

  //Lado Direito
  motor1.setSpeed(velocidadeA);
  motor2.setSpeed(velocidadeA);
  //Lado Esquerdo
  motor3.setSpeed(velocidadeB);
  motor4.setSpeed(velocidadeB);
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
}

//============

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
<<<<<<< HEAD
  mensagemVelocidadeE = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagemVelocidadeD = atoi(strtokIndx);     // convert this part to an integer
=======
  mensagemVelocidadeD = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagemVelocidadeL = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagemPower = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  mensagemSentido = atoi(strtokIndx);     // convert this part to an integer

>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac

  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
  Serial.print("Robô: ");
  Serial.println(messageFromPC);
  Serial.print("Velocidade Rodas Direitas: ");
  Serial.println(mensagemVelocidadeD);
  Serial.print("Velocidade Rodas Esquerdas:");
<<<<<<< HEAD
  Serial.println(mensagemVelocidadeE);
=======
  Serial.println(mensagemVelocidadeL);
>>>>>>> d565adb0393e27f35314c2cdba48e2186693c2ac
}
