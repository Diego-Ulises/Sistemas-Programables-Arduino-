 /* Carro Inalambrico Bluetooth_Ultrasonico
   
  ARDUINO   L298N (Puente H)

  9          N3
  10         N4
  6          N1
  5          N2


  Conexion del Modulo Bluetooth HC-06 y el Arduino

  ARDUINO    Bluetooth HC-06

  0 (RX)       TX
  1 (TX)       RX
  5V           VCC
  GND          GND


  Conexion Sensor Ultrasonido HC-SR04

  ARDUINO    Ultrasonido HC-SR04
  2            Echo
  3            Trig
  5V           VCC
  GND          Gnd
  
  */
  
   int izqA = 5;
   int izqB = 6;
   int derA = 9;
   int derB = 10;
   
   int vel = 255;
   int estado = 'g';
            
   int LED=7;
   
   int Echo = 2;            
   int Trig = 3;            
  

   void setup(){

   Serial.begin(9600);    
  
   pinMode(Trig, OUTPUT);   
   pinMode(Echo, INPUT);  
   
   pinMode(13, OUTPUT);
   pinMode(LED, OUTPUT);
   
   pinMode(derA, OUTPUT);
   pinMode(derB, OUTPUT);
   pinMode(izqA, OUTPUT);
   pinMode(izqB, OUTPUT);
   
   }


   void loop(){

   if (Serial.available()>0){
   estado = Serial.read();
   }

   
   if (estado == 'a'){       // Adelante
   
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(derA, vel);
   analogWrite(izqA, vel);
   digitalWrite(LED, HIGH); 
  }

   if (estado == 'b'){      // Izquierda
   
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(derA, 0);
   analogWrite(izqA, vel);
   digitalWrite(LED, HIGH);  
  }

   if (estado == 'c') {     // Detenido
   
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(derA, 0);
   analogWrite(izqA, 0);
   digitalWrite(LED, HIGH);  
  }


   if (estado == 'd'){      // Derecha
   
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(izqA, 0);
   analogWrite(derA, vel);
   digitalWrite(LED, HIGH);  
  }


   if (estado == 'e'){      // Reversa
   
   analogWrite(derA, 0);
   analogWrite(izqA, 0);
   analogWrite(derB, vel);
   analogWrite(izqB, vel);
   digitalWrite(LED, HIGH);  
  }
  

   if (estado == 'f'){        // Se mueve sensando distancia

   long duracion;
   long distancia;

   digitalWrite(Trig, LOW);
   delayMicroseconds(2); 
   digitalWrite(Trig, HIGH);   
   delayMicroseconds(10);
   digitalWrite(Trig, LOW);
   
   duracion= pulseIn(Echo, HIGH);
   duracion= duracion/2;
   distancia= duracion/29;

   digitalWrite(LED, HIGH); 

   
   if (distancia <=25 && distancia >=2){    
   digitalWrite(13, HIGH);                   

   analogWrite(derB, 0);                     
   analogWrite(izqB, 0);
   analogWrite(derA, 0);
   analogWrite(izqA, 0);
   delay (200);

   analogWrite(derB, vel);                   
   analogWrite(izqB, vel);
   delay(500);

   analogWrite(derB, 0);                     
   analogWrite(izqB, 0);
   analogWrite(derA, 0);
   analogWrite(izqA, vel);
   delay(1000);

   digitalWrite(13, LOW);
    
   }


   else{                                    
    
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(derA, vel);
   analogWrite(izqA, vel);
      
  }
  }


   if (estado == 'g'){                      
   
   analogWrite(derB, 0);
   analogWrite(izqB, 0);
   analogWrite(derA, 0);
   analogWrite(izqA, 0);
   digitalWrite(LED, LOW); 
    
  }
  }
