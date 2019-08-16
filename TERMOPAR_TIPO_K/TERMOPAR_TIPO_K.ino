//MEDIDOR DE TEMPERARTURA CON MAX6675 y LCD.

#include "max6675.h"

#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x27, 16, 22);

  //Se crea una variable flotante para almacenar la temperatura.

  int temperatura1 = 0;
  int temperatura2 = 0;
  int temperatura3 = 0;
  int temperatura4 = 0;
  int temperatura1f = 0;
  int temperatura2f = 0;
  int temperatura3f = 0;
  int temperatura4f = 0;

  
  //Se definen los pines a usar para conectar el modulo MAX6675

  int SO1 = 2;
  int CS1 = 3;
  int CSK1 = 4;

  int SO2 = 5;
  int CS2 = 6;
  int CSK2 = 7;

  int SO3 = 8;
  int CS3 = 9;
  int CSK3 = 10;

  int SO4 = 11;
  int CS4 = 12;
  int CSK4 = 13;  

  MAX6675 ktc1(CSK1, CS1, SO1);
  MAX6675 ktc2(CSK2, CS2, SO2);
  MAX6675 ktc3(CSK3, CS3, SO3);
  MAX6675 ktc4(CSK4, CS4, SO4);

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.clear();

  //activa comunicacion serial.

  Serial.begin(9600);
}

void loop() {

  //Leer temperatura.

  temperatura1 = ktc1.readCelsius();
  temperatura1f = ktc1.readFahrenheit();
  Serial.print("Temperatura 1: ");
  Serial.print(temperatura1);
  Serial.print("° Celsius / ");
  Serial.print(temperatura1f);
  Serial.println("° Fahrenheit");
  
  temperatura2 = ktc2.readCelsius();
  temperatura2f = ktc2.readFahrenheit();
  Serial.print("Temperatura 2: ");
  Serial.print(temperatura2);
  Serial.print("° Celsius / ");
  Serial.print(temperatura2f);
  Serial.println("° Fahrenheit");

  temperatura3 = ktc3.readCelsius();
  temperatura3f = ktc3.readFahrenheit();
  Serial.print("Temperatura 3: ");
  Serial.print(temperatura3);
  Serial.print("° Celsius / ");
  Serial.print(temperatura3f);
  Serial.println("° Fahrenheit");

  temperatura4 = ktc4.readCelsius();
  temperatura4f = ktc4.readFahrenheit();
  Serial.print("Temperatura 4: ");
  Serial.print(temperatura4);
  Serial.print("° Celsius / ");
  Serial.print(temperatura4f);
  Serial.println("° Fahrenheit");
  
  Serial.println("");
  Serial.println("");
  
  //Mostrar dato de temperatura en LCD.

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print(temperatura1);
  lcd.setCursor(6, 1);
  lcd.print((char)223);
  lcd.print("C");

  //Pausa para repetir el proceso.
  
  delay(3000);
}

