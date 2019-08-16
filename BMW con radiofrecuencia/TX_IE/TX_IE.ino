/*  ----------------------------------------------------------------
  Código Para el Transmisor.

  Arduino MEGA.  Módulo NRF24LD1.
  
  Vcc           5V
  GND           GND
  
  Pin 7         CE
  Pin 8         CSN
  
  Pin 52        SCK
  Pin 51        MOSI
  Pin 50        MISO
  --------------------------------------------------------------------
*/

// Librerías.
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN.

//Canal de comunicación. 
const byte canal[]={"31"};

// Vector que envia el eje X y Y.
int ejes[]={0,0};

// Variables donde se almacena el valor del eje X y del eje Y del Joystick.
int ejeX=0;
int ejeY=0;

void setup(){
  
  radio.begin();
  radio.openWritingPipe(canal[1]); // Canal 31.
  radio.setPALevel(RF24_PA_MAX); // Máxima potencia de transmisión.
 
}

void loop(){
  
  radio.stopListening();
  
  ejeX = analogRead(A0);
  ejeY = analogRead(A1);
  
  ejes[0]=ejeX;
  ejes[1]=ejeY;
  
  radio.write(&ejes, sizeof(ejes));
    
}
