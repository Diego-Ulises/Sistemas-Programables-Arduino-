  #include <Wire.h>

  void setup(){
  
  //Pines en modo salida.
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT); 
  
  //Led.
  
  pinMode(8, OUTPUT); 
  
  //Unimos este dispositivo al bus I2C con dirección 1.
 
  Wire.begin(1);
 
  //Registramos el evento al recibir datos.
  Wire.onReceive(receiveEvent);

  }
 
  void loop(){
  delay(300);
  }
 
  // Función que se ejecuta siempre que se reciben datos del master
  // siempre que en el master se ejecute la sentencia endTransmission
  // recibirá toda la información que hayamos pasado a través de la sentencia Wire.write

  void receiveEvent(int howMany){
  
  int estado = Wire.read();
  
  // Activamos / desactivamos las salidas.
  
  digitalWrite(2,estado);
  digitalWrite(3,estado);
  digitalWrite(4,estado);
  digitalWrite(5,estado);
  digitalWrite(6,estado);
  digitalWrite(7,estado);
  digitalWrite(8,estado);

  }

