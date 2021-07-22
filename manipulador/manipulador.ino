#include <Servo.h>

const byte numChars = 64;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int mensagemAngulo = 0;

//float floatFromPC = 0.0;

boolean newData = false;

Servo base;
Servo elo2;
Servo elo3;
Servo elo4;
Servo elo5;
Servo garra;

int slider0 = 0;
int slider1 = 0;
int slider2 = 0;
int slider3 = 0;
int slider4 = 0;

bool fechar = false;


//============

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("O arduino espera uma mensagem do tipo <String, int, int>");

  base.attach(4);
  elo2.attach(5);
  elo3.attach(6);
  elo4.attach(7);
  elo5.attach(8);
  
  garra.attach(9);
  
//  base.write(90);
//  elo2.write(90);
//  elo3.write(90);
//  elo4.write(90);
//  elo5.write(90);
//  garra.write(90);
  
  delay(15);
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

  //Valores vindo dos sliders
  if (strcmp(messageFromPC, "value0") == 0) {
    slider0 = mensagemAngulo;
  }

  //Esperando a string 'value1' para a velocidade da roda direita
  if (strcmp(messageFromPC, "value1") == 0) {
    slider1 = mensagemAngulo;
  }

  if (strcmp(messageFromPC, "value2") == 0) {
    slider2 = mensagemAngulo;
  }

  if (strcmp(messageFromPC, "value3") == 0) {
    slider3 = mensagemAngulo;
  }

  if (strcmp(messageFromPC, "value4") == 0) {
    slider4 = mensagemAngulo;
  }

//  if (strcmp(messageFromPC, "inverter") == 0) {
//    fechar = !fechar;
//  }

  controle();


}

//============

void controle() {
  
//  if (fechar == true){
//    a.write(180);
//  }
//  else a.write(180);

  base.write(slider0);
  elo2.write(slider1);
  elo3.write(slider2);
  elo4.write(slider3);
  elo5.write(slider4);
  delay(100);
}

//============

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
  mensagemAngulo = atoi(strtokIndx);     // convert this part to an integer


  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
  Serial.print("Servo: ");
  Serial.println(messageFromPC);
  Serial.print("Int: ");
  Serial.println(mensagemAngulo);

}
