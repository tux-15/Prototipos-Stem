void motorRun(int meioPeriodo, boolean direcao);
void debug();

// Pinos do driver A4988
const int stepPin = 4;
const int dirPin = 3;
const int pinIR_1 = 6;

int valorPot = 0;
int meioPeriodo = 1000; // tempo que o pino stepPin fica HIGH ou LOW gerando um pulso quadrado. Mexende nesse valor, pode alterar a frequância de rotação do motor
int ir = 0;

int RPM = 0;

void setup () 
{
  pinMode (stepPin, OUTPUT);
  pinMode (dirPin, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(9600);
}

void loop()
{
    ir = digitalRead(pinIR_1);
    valorPot = analogRead(A0);
    meioPeriodo = map(valorPot, 0,1023, 500, 10000);  // Frequência com range de 300 RPM a 15 RPM

   if(ir == 0)
   {
     Serial.println("Parado");
   }

  else
  {  
    motorRun(meioPeriodo, HIGH);
  }
}

void motorRun(int meioPeriodo, boolean direcao)
{
  //Muda a direção da rotação
  digitalWrite(dirPin,direcao);

  digitalWrite(stepPin,HIGH);
  delayMicroseconds(meioPeriodo);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(meioPeriodo);
}

void debug()
{
  float PPS = 1000000 / (2 * meioPeriodo); // Frequencia Pulsos por segundo
  RPM = (PPS * 60) / 200;            // Calculo do RPM
  Serial.print("  RPM: ");
  Serial.println(RPM);
}
