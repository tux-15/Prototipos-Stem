#include <Servo.h>

const byte numChars = 64;       //Número máximo de caracteres por mensagem
char receivedChars[numChars];   //Armazenar mensagem
char tempChars[numChars];       // Array temporário para parsing

// Armazenar mensagem depois do parsing

char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int integerFromPC2 = 0;

//Adicionar mais conforme necessidade
//float floatFromPC = 0.0;

boolean newData = false;

long previousMillis = 0; 
long interval = 250;  

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  Serial.begin(9600);
  Serial.println("<Manipulador iniciando, 0, 0>");

  servo1.attach();
  servo2.attach();
  servo3.attach();
  servo4.attach();
  servo5.attach();

}

void loop() {

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
  
    Serial.println("<arduino says Hi, 3, 4>");
  //Serial.print("I got: "); Serial.print(integerFromPC); Serial.println();
  }

  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    newData = false;
  }
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // caractere de terminação
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

void parseData() {      // Dividir a mensagem em partes

    char copy_receivedChars[sizeof(receivedChars)] = "";
    strcpy(copy_receivedChars, receivedChars);

    char * strtokIndx; // Índice de srttok()

    strtokIndx = strtok(copy_receivedChars,",");     // Pegar primeira parte (String)
    strcpy(messageFromPC, strtokIndx);      // Armazenar em messageFromPC 
 
    strtokIndx = strtok(NULL, ",");         // Continuar a dividir a mensagem
    integerFromPC = atoi(strtokIndx);       // Converte para interiro e armazena na variável

    strtokIndx = strtok(NULL, ",");         // Repete a operação anterior
    integerFromPC2 = atoi(strtokIndx);      // Repetir para quantas partes forem necessárias

    // strtokIndx = strtok(NULL, ",");
    // floatFromPC = atof(strtokIndx);      // Caso seja necessário receber um float

}
