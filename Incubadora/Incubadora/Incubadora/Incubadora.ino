  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <LiquidCrystal.h>
  LiquidCrystal_I2C lcd(0x27,16,22);
  
  # include "DHT.h"
  # define DHTPIN 12           // Señal del DTH11
  # define DHTTYPE DHT11       
  DHT dht(DHTPIN, DHTTYPE);
  
  int rele = 13;              // Señal del Rele
  int vcc = 11;               // Vcc del DTH11
  int vcc2 = 10;              // Vcc del Rele
  int vent = 9;               // Pin ventilador
  
  void setup(){
    
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(rele, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(vcc2, OUTPUT);
  dht.begin();
  pinMode(vent,OUTPUT);
  
  }

  void loop(){

  digitalWrite(vcc, HIGH);
  digitalWrite(vcc2, HIGH);
  
  int h = dht.readHumidity();    // Lee la humedad
  int t = dht.readTemperature();

  lcd.clear();                   
  lcd.setCursor(0, 0);           
  lcd.print("Humedad: ");
  lcd.setCursor(8, 0);
  lcd.print(h);                 //Escribe la humedad
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temperatura: ");
  lcd.setCursor(12, 1);
  lcd.print(t);                 //Escribe la temperatura
  lcd.print((char)223);
  lcd.print("C");
  delay (1000);

  if (t > 24 && t<26){
    
  digitalWrite(rele, LOW);
  digitalWrite(vent, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lampara Inactiva");
  delay(1000);
  
  }
  
  else if(t<24){  
  
  digitalWrite(rele, HIGH);
  digitalWrite(vent, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lampara Activa");
  
  delay(1000);
  
  }
  
  else if(t>26){
  digitalWrite(rele, LOW);
  digitalWrite(vent, HIGH);  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lampara Inactiva");
  
  delay(1000);
  
  }
  }
