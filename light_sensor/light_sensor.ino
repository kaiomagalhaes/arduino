/*******************************************************************************
* Master Kit - Construindo um Sensor de Luz 1
* Imprime na Serial o valor de tensão do LDR.
*******************************************************************************/

const int pinoLDR = A0; // pino onde o LDR está conectado
int leitura = 0; // variável para armazenar o valor lido pelo ADC
float tensao = 0.0; // variável para armazenar a tensão
const int pinoLED = 7; // pino onde o LED está conectado

void setup() {
  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  // configura o pino com LDR como entrada
  pinMode(pinoLDR, INPUT); // pino A0
  pinMode(pinoLED, OUTPUT); // pino A0
}

void loop() {
  // le o valor de tensão no pino do LDR
  leitura = analogRead(pinoLDR);

  // imprime valor lido pelo arduino (0 a 1023)
  Serial.print("Leitura: ");
  Serial.print(leitura);
  Serial.print("\t"); // tabulacao

  // converte e imprime o valor em tensão elétrica
  tensao = leitura * 5.0 / 1024.0;
  Serial.print("Tensão: ");
  Serial.print(tensao);
  Serial.print("V");
  Serial.print("\t"); // tabulacao



  if(leitura < 400){ // se a luminosidade for menor que 40
    digitalWrite(pinoLED,HIGH); // acende o LED
    Serial.print("Light: ON");
  }
  else { // se não
         Serial.print("Light: OFF");

    digitalWrite(pinoLED,LOW); // apaga o LED
  }
  Serial.println(); // nova linha

}