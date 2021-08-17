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
long interval = 1000;  

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void checkNewData();
void sendMessage();
void moveServo();
void startPosition();

void setup() {
  
  Serial.begin(9600);
  delay(250);
  

  servo1.attach(8);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);

  startPosition();

  Serial.println("<Manipulador iniciando, 0, 0>");

}

void loop() {

  sendMessage("Manipulador", 1, 1);
  recvWithStartEndMarkers();
  checkNewData();
  moveServo(messageFromPC, integerFromPC);

}

void startPosition(){
  servo1.write(90);
  servo2.write(9);
  servo3.write(10);
  servo4.write(60);
  servo5.write(66);
  
}

void moveServo(char servo[numChars], int angle){
  
  if (strcmp(servo, "value0") == 0){
    servo1.write(angle);
  }
  
  if (strcmp(servo, "value1") == 0){
    servo2.write(angle);
  }
  
  if (strcmp(servo, "value2") == 0){
    servo3.write(angle);
  }
  
  if (strcmp(servo, "value3") == 0){
    servo4.write(angle);
  }
  
  if (strcmp(servo, "value4") == 0){
    servo5.write(angle);
  }
}


void sendMessage(char message[numChars], int num1, int num2){

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    Serial.print("<");
    Serial.print(message);Serial.print(", ");
    Serial.print(num1);Serial.print(", ");
    Serial.print(num2);Serial.println(">");
  }
}

void checkNewData(){
  
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
