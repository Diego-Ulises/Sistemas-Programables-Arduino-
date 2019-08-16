/*  ----------------------------------------------------------------  
  Código Para el Receptor.

  Arduino UNO.   Módulo NRF24LD1.
  
  Vcc           5V
  GND           GND
  
  Pin 7         CE
  Pin 8         CSN
  
  Pin 13        SCK
  Pin 11        MOSI
  Pin 12        MISO
  --------------------------------------------------------------------
*/

// Librerías.
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN.

//Canal de comunicación. 
const byte canal[]={"31"};

int X = 0;
int Y = 0;
int ejes[]={500, 500};

// Motor A.
int ENA = 6;
int IN1 = 5;
int IN2 = 9;

// Motor B.
int ENB = 2;
int IN3 = 10;
int IN4 = 3;

int izqA = IN2;
int izqB = IN1;
int derA = IN3;
int derB = IN4;

// Variador de velocidad.
int vel;

void setup(){
  
  radio.begin();
  radio.openReadingPipe(1, canal[1]); // Canal 31.
  radio.setPALevel(RF24_PA_MAX); // Máxima potencia de transmisión.

  // Pines del Puente H declarados como salidas.
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

 // Se escriben en 0 para que esten detenidos los motores al inicio.
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(izqA, 0);
}

void loop(){
  
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()){

      radio.read(&ejes, sizeof(ejes));

      X = ejes[0];
      Y = ejes[1];


      // Adelante
      if (Y > 520){
        vel = map(Y, 520, 1023, 0, 255);
        analogWrite(derB, 0);
        analogWrite(izqB, 0);
        analogWrite(derA, vel);
        analogWrite(izqA, vel);
      }

      // Reversa
      if (Y < 480) {   
        vel = map(Y, 0, 480, 255, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
        analogWrite(derB, vel);
        analogWrite(izqB, vel);
      }

      // Derecha
      if (X > 520) {  
        analogWrite(derB, 0);
        analogWrite(izqB, 0);
        analogWrite(izqA, 0);
        analogWrite(derA, map(X, 520, 1023, 0, 255));
      }

      // Izquierda
      if (X < 480) {  
        analogWrite(derB, 0);
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, map(X, 0, 480, 255, 0));
      }

      //Estado neutro.
      if (X > 480 && X < 520 && Y > 480 && Y < 520){
        analogWrite(derB, 0);
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
      }
      
    }
  }
}
