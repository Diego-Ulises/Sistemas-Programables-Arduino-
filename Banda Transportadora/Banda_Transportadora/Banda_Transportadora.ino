#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);
#include <Wire.h>

// Motor A.

int ENA = 10;
int IN1 = 9;
int IN2 = 8;

// Motor B.

int ENB = 5;
int IN3 = 7;
int IN4 = 6;

//Velocidad.

int vel = 200;

//Pin virtual para ardusens.

int vcc2 = 4;

//Modulo ardusens.

int leds = 8;
float ldr;

//Pines del ultrasonico.

int Echo = 12;
int Trig = 11;

//Contador de objetos.

int contador = 0;

//Distancia del objeto proximo.

long distancia = 0;
int dist;

//Temperatura y Humedad.

# define DHTPIN 3           // Señal del DTH11
# define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup () {

  //Pines de los motores con su variador de velocidad.

  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  //Pin Virtual para ardusens

  pinMode (vcc2, OUTPUT);


  //Leds del modulo Ardusens.

  pinMode(4, OUTPUT);

  //Buzzer.

  pinMode(2, OUTPUT);

  //Pines del Ultrasonico.

  pinMode (Trig, OUTPUT);
  pinMode (Echo, INPUT);

  //Fotoresistencia.

  pinMode(A1, INPUT);

  Serial.begin(9600);

  //Master al bus I2C.

  Wire.begin();

  dht.begin();

  //LCD.

  lcd.init();
  lcd.backlight();
  lcd.clear();

}

byte estado = 1;
int dato = 'g';


void loop () {

  digitalWrite(2, LOW);

  Master();
  digitalWrite(vcc2, HIGH);

  if (Serial.available() > 0) {

    dato = Serial.read();

  }

  if (dato == 'd') {
    Adelante();
    delay(10);
  }

  if (dato == 'b') {
    Atras();
    delay(10);
  }

  if (dato == 'c') {
    if (estado == 1) {
      digitalWrite(2, HIGH);
      estado = 0;
      delay(300);
    }

    else if (estado == 0) {
      estado = 1;
      delay(300);
    }

    Parar();
  }

  if (dato == 'a') {
    vel = 250;
  }

  if (dato == 'e') {
    vel = 180;
  }

  if (dato == 'f') {
    estado = 1;
  }

  if (dato == 'g') {
    estado = 0;
  }

  //Temperatura Y Humedad.

  int h = dht.readHumidity();    // Lee la humedad
  int t = dht.readTemperature();

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.setCursor(4, 1);
  lcd.print(h);                 //Escribe la humedad
  lcd.print("%");

  lcd.setCursor(8, 1);
  lcd.print("Temp: ");
  lcd.setCursor(13, 1);
  lcd.print(t);                 //Escribe la temperatura
  lcd.print((char)223);
  lcd.print("C");

  Serial.println(String("Temperatura: ") + String (t) + String("°C"));
  Serial.println(String("Humedad: ") + String (h) + String("%"));

  //Contador.

  lcd.setCursor(0, 0);
  lcd.print("Cont:");
  lcd.setCursor(5, 0);
  lcd.print(contador);

  //Distancia.

  if (dist < 40) {
    lcd.setCursor(8, 0);
    lcd.print("Dist:");
    lcd.setCursor(13, 0);
    lcd.print(dist);
    Serial.println(String("Distancia: ") + String (dist));
  }
}

void Master() {

  //Transmisión al dispositivo 1.
  Wire.beginTransmission(1);

  //Enviamos un byte, L pondrá en estado bajo y H en estado alto.
  Wire.write(estado);

  //Paramos la transmisión.
  Wire.endTransmission();
  
}

void Adelante() {

  Fotoresistencia();

  //Direccion motor A.

  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, vel); //Velocidad motor A

  //Dirección motor B.

  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, vel); //Velocidad motor B

  delay(100);
  analogWrite (ENA, 0); //Velocidad motor A
  analogWrite (ENB, 0); //Velocidad motor B

  //Sensor Ultrasonico.

  long duracion;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duracion = pulseIn(Echo, HIGH);
  duracion = duracion / 2;
  distancia = duracion / 29;
  dist = (int)distancia;
}

void Fotoresistencia() {

  ldr = analogRead(A1);
  if (ldr < 800) {
    if (contador < 50) {
      contador++;
    }
    digitalWrite(4, LOW);
    delay(500);
  }

  if (ldr > 800) {
    digitalWrite(4, HIGH);
  }

  Serial.println(String("Fotoresistencia: ") + String (ldr));
}

void Atras () {

  //Direccion motor A.

  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, vel); //Velocidad motor A

  //Direccion motor B.

  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, vel); //Velocidad motor B
  delay(100);

  analogWrite (ENA, 0); //Velocidad motor A
  analogWrite (ENB, 0); //Velocidad motor B
}

void Parar() {

  //Direccion motor A.

  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  analogWrite (ENA, 0); //Velocidad motor A

  //Direccion motor B.

  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, 0); //Velocidad motor A
}
