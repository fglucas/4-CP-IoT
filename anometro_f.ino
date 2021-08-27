#include <ArduinoJson.h>

// --- Constantes ---
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)

const int TAMANHO = 200;

int TermistorPin = A0;
int SensorUV = A1;
int Vo, Vout, key;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, temp, templast, Rldr, L, expo, expolast, Rdark;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


// --- Variáveis Globais ---
unsigned int Sample  = 0;        //Armazena o número de amostras
unsigned int counter = 0;        //Contador para o sensor
unsigned int RPM = 0;            //Rotações por minuto
float speedwind = 0;             //Velocidade do vento (km/h)



// --- Configurações Inicias ---
void setup() {
  pinMode(2, INPUT);        //configura o digital 2 como entrada
  digitalWrite(2, HIGH);    //internall pull-up active

  Serial.begin(115200);       //inicia serial em 9600 baud rate
} //end setup

// --- Loop Infinito ---
void loop() {

  Sample++;
  Serial.print(Sample);
  Serial.print(": Iniciando Leitura...");

  windvelocity();

  Serial.println("   Finalizado.");

//print RPM
  Serial.print("Contador de voltas: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);

//print km/h
  Serial.println(";  Vel. Vento: ");
  SpeedWind();
  Serial.print(speedwind);
  Serial.println(" [km/h] ");
  Serial.println(" ");

  temp = readTemp(TermistorPin);
  printTemp(temp);

  expo = readUV(SensorUV);
  printLDR(expo);

// Area JSON
  StaticJsonDocument<TAMANHO> json;

  int JsensorUV = readUV(SensorUV); 
  int JsensorTemp = readTemp(TermistorPin);
  float JsensorWind = speedwind;



  json["exposicaoUV"] = JsensorUV; // data para JSON


  json["TempGraus"] = JsensorTemp; // data para JSON


  json["Ventokmh"] = JsensorWind; // data para JSON

  serializeJson(json, Serial);
  Serial.println();


  delay(delaytime);                        //taxa de atualização
} //end setup

// função para leitura de Temperatura 
float readTemp(int ThermistorPin){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); 
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));// Equação de Steinhart–Hart 
  Tc = T - 273.15; //temp em Graus celcius
  //Tf = (Tc * 9.0)/ 5.0 + 32.0; // temp em fahrenheit
  return Tc;
}

// função para leitura de Luminosidade
float readUV(int ShensorUV){
  Vout = analogRead(ShensorUV);
  Rdark = 127410;
  Rldr = 10000 * (1023.0 / (float)Vout -1.0);
  L =  pow ((Rdark / Rldr),  1 / 0.8582);
  return L;
}

// função para print TEMPERATURA
void printTemp(float Tc) {

  Serial.print("Temperatura: ");
  Serial.print(Tc);
  Serial.println(" C");
  Serial.println(" ");
}

// função para print Luminosidade
void printLDR(float L) {

  Serial.print("Exposicao UV: ");
  Serial.println(L);
  Serial.println(" ");
}



//Função para medir velocidade do vento
void windvelocity() {
  speedwind = 0;


  counter = 0;
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + period) {}
}

//Função para calcular o RPM
void RPMcalc() {
  RPM = ((counter) * 60) / (period / 1000); // Calculo rotações por minuto (RPM)
}


//Velocidade do vento em km/h
void SpeedWind() {
  speedwind = (((2 * pi * radius * RPM) / 60) / 1000) * 3.6; //Calcula velocidade do vento em km/h
} //end SpeedWind

//Incrementa contador
void addcount() {
  counter++;
}


