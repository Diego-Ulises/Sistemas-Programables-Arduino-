
# include <LiquidCrystal_I2C.h>         // Libreria para la LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);     // Tamaño de filas y columnas del LCD

//PINES del Sensor Ultrasónico.
const int Echo = 10;            
const int Trig = 11; 

// PIN de LED AZUL.
const int LED = 13;

//PIN de RELÉ.
const int relay = 2;

void setup() {
   
   Serial.begin(9600);    
  
   pinMode(Trig, OUTPUT);   
   pinMode(Echo, INPUT);
     
   pinMode(LED, OUTPUT);
   
   pinMode(relay,OUTPUT);
   
   lcd.init();                     // Se inicializa el display LCD
   lcd.backlight();                // Se enciende la luz de fondo de la LCD
   lcd.clear();                    // Limpia los simbolos de la pantalla LCD
}

void loop() {
   
   float duracion;
   float distancia;

   digitalWrite(Trig, LOW);
   delayMicroseconds(2); 
   digitalWrite(Trig, HIGH);   
   delayMicroseconds(10);
   digitalWrite(Trig, LOW);
   
   duracion= pulseIn(Echo, HIGH);
   duracion= duracion/2;
   distancia= duracion/29;

   lcd.clear();                 
   lcd.setCursor(0, 0);
   lcd.print(String("Dist: ") + String(distancia));  
          
   if (distancia > 15 && distancia < 20){   
    digitalWrite(LED, HIGH); 
    digitalWrite(relay, HIGH);                
   }else if(distancia < 5){
    digitalWrite(LED, LOW); 
    digitalWrite(relay, LOW); 
   } 
   
   if(digitalRead(relay)==HIGH){
    lcd.setCursor(0, 1);                             
    lcd.print("Activa  ");  
   }else{
    lcd.setCursor(0, 1);                             
    lcd.print("Inactiva"); 
   }
   
   if(distancia >5 && distancia < 15){
     lcd.setCursor(8, 1);                             
     lcd.print(" - MEDIO");
   }else if(distancia >15){
     lcd.setCursor(8, 1);                             
     lcd.print(" - VACIO");
   }if(distancia <6){
     lcd.setCursor(8, 1);                             
     lcd.print(" - LLENO");  
   }
    Serial.println(distancia);        
   delay(100);
}g
