/*  ----------------------------------------------------------------
   
  Codigo del Transmisor

  Arduino MEGA  Módulo NRF24LD1
  
  Vcc           5V
  GND           GND
  
  Pin 7         CE
  Pin 8         CSN
  
  Pin 52        SCK
  Pin 51        MOSI
  Pin 50        MISO
    
  --------------------------------------------------------------------
*/

#include <SPI.h>      //Libreria para usar el modulo SPI 
#include "nRF24L01.h" //Librerias del modulos nRF24L01+
#include "RF24.h"

RF24 radio(7, 8);//Declaracion de los pines de control CE y CSN para el modulo, se define "radio"

// Definicion de las direcciones de comunicacion

const uint64_t direccion1 = 0x7878787878LL;
const uint64_t direccion2 = 0xB3B4B5B6F1LL;

//Declaracion de todas las variables

unsigned int RX[128];
unsigned int TX[128]; 
unsigned char mul = 1;
bool TX_state = false;

int  error_cont = 0;
bool test = 0;

void setup(void){
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(230400); //Inicializacion del puerto serial para la comunicacion con la PC

  radio.begin(); //Inicio del modulo nRF24L01+
  radio.setPALevel(RF24_PA_HIGH);  // Configuracion en modo de maxima potencia
  radio.setDataRate(RF24_250KBPS); //Configuracion de la velocidad de transmision
  radio.setChannel(100); // Configuracion del canal de comunicacion
  
  //Apertura de los canales de comunicacion
  
  radio.openWritingPipe(direccion1);
  radio.openReadingPipe(1, direccion2);

  //Mensaje inicial
  
  Serial.println("Sistema de verificacion de coherencia en");
  Serial.println("envio de datos con el modulo nRF24L01+");
  
  for (int x = 0; x < 128; x++){
    
    RX[x] = 0;
    TX[x] = 0;
  }

}


void loop(void){
 
  if (Serial.available()){
    
    if (TX_state == false)
    {
      unsigned char temp = Serial.read();
      if (temp == '1')
      {
        TX_state = true;
        return;
      } else
      {
        mul = temp - 48;
        
        Serial.print("Cambio de multiplicador por ");
        Serial.println(mul);
      }
    }
  }

  if (TX_state == true)
  {
    Serial.println("Iniciando envios");
    Serial.print("Multiplicador= ");
    Serial.println(mul);
    Serial.println("******************************************************************");
    
    for (unsigned char i = 0; i < 128; i++)
    {
      radio.stopListening(); // Paramos la escucha para poder escribir
  
      TX[i] = i * mul;
      bool ok = radio.write(&TX[i], sizeof(TX[i])); //Envio de datos
      if (!ok)
      {
        Serial.print("fallo el envio en el dato ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(TX[i]);
        
      } else
      {
        
        Serial.print("Dato ");
        Serial.print(i);
        Serial.print(" enviado: ");
        Serial.println(TX[i]);
      }
  
   
      radio.startListening(); //Volvemos a la escucha
      unsigned long inicio = millis();
      bool timeout = false;
     
      while ( ! radio.available() && ! timeout )
      {
        if (millis() - inicio > 300 )  // Esperamos 3000ms para darle tiempo a el receptor de respondernos
          timeout = true; // si se alcanzo el tiempo, se pone en true para
      }
      if ( timeout )
      {
        Serial.print("fallo la recepcion de el dato ");
        Serial.println(i);
        RX[i] = 0;
      } else
      {
        radio.read( &RX[i], sizeof(RX[i])); //Funcion de lectura de datos
        Serial.print("Dato ");
        Serial.print(i);
        Serial.print(" recibido: ");
        Serial.println(RX[i]);
      }
  
    }
    Serial.println("Todos los datos fueron transmitidos");
    Serial.println("******************************************************************");
    radio.startListening(); //Volvemos a la escucha
    TX_state = 0;
    test = 1;
  }
  
  if (test == 1)
  {
    Serial.println("******************************************************************");
    Serial.println("Iniciando verificacion de caracteres");
    error_cont = 0;
    for (unsigned char i = 0; i < 128; i++)
    {
      if (TX[i] != RX[i])
      {
        Serial.print("Datos erroneos en la comparacion: ");
        Serial.println(i);
        error_cont++;
      } else
      {
        Serial.print("Datos ");
        Serial.print(i);
        Serial.println(" correctos");
      }
    }
    Serial.println("********************************************************************");
    Serial.println("Test finalizado...");
    Serial.print("Numero de datos errorenos recividos: ");
    Serial.println(error_cont);
    test = 0;
    error_cont = 0;
    for (int x = 0; x < 128; x++)
    {
      RX[x] = 0;
      TX[x] = 0;
    }
  }
}
