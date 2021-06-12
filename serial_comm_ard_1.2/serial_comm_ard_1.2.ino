const byte numChars = 64;       //Número máxim de caracteres por mensagem
char receivedChars[numChars];   //Armazenar mensagem
char tempChars[numChars];       // Array temporário para parsing


// Armazenar mensagem depois do parsing

char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int integerFromPC2 = 0;

//Adicionar mais conforme necessidade
//float floatFromPC = 0.0;

boolean newData = false;

//============

void setup() {
    Serial.begin(9600);
    Serial.println("O arduino espera uma mensagem do tipo <String, int, int>");
    Serial.println();
}

//============

void loop() {

    //Comunicação e parsing -----------------------------
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // Cópia temporária dos dados
            //   Para garantir que a eliminação do line terminator não corrompa dos dados
        parseData();

    //===================================================

    //Resto do código que depende de haver nova mensagem
        showParsedData(); //Mandar pela serial os dados recebidos para demo

        newData = false; //Esperar por nova mensagem
    }
    //Resto do código que não depende de haver nova mensagem
    //Serial.println("<This is coming from the Arduino>");
    //delay(100);
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

    char * strtokIndx; // Índice de srttok()

    strtokIndx = strtok(tempChars,",");     // Pegar primeira parte (String)
    strcpy(messageFromPC, strtokIndx);      // Armazenar em messageFromPC 
 
    strtokIndx = strtok(NULL, ",");         // Continuar a dividir a mensagem
    integerFromPC = atoi(strtokIndx);       // Converte para interiro e armazena na variável

    strtokIndx = strtok(NULL, ",");         // Repete a operação anterior
    integerFromPC2 = atoi(strtokIndx);      // Repetir para quantas partes forem necessárias

    // strtokIndx = strtok(NULL, ",");
    // floatFromPC = atof(strtokIndx);      // Caso seja necessário receber um float

}

//============

void showParsedData() {
    Serial.print("Mensagem: ");
    Serial.println(messageFromPC);
    Serial.print("Int 1: ");
    Serial.println(integerFromPC);
    Serial.print("Int 2: ");
    Serial.println(integerFromPC2);
}
