  # include <LiquidCrystal_I2C.h>         // Libreria para la LCD 
  LiquidCrystal_I2C lcd(0x27, 16, 2);     // Tamaño de filas y columnas del LCD
  # include <Wire.h>                      // Libreria para el protocolo I2C


  int vcc = 11;                   // Crear pin de 5v para alimentar el sensor de suelo
  int vcc2 = 10;                  // Crear pin de 5v para alimentar el relé
  const int sensor = A0;          // Pin en el que está conectado el sensor de suelo
  const int Rc = 1000;            // Resistencia de calibración
  const int relay = 2;            // Pin en que está conectado el Relay
  int V;                          // variable donde se guarda el valor del sensor de suelo
  int contador = 0;               // Nos va a contar el numero de riegos
  long Rsensor;                   // Resistencia del sensor de suelo
  long Resk;                      // valor de la resistencia 
  unsigned long tr = 1.5;         // Tiempo de regado en segundos                                    // AJUSTAR
  unsigned long tespera = 0;      // Tiempo de espera en segundos                                    // AJUSTAR
  const int rr = 10;              // Resistencia (en kohmios) a partir de la cual empieza a regar    // AJUSTAR


  void setup(){                   // Se ejecuta una sola vez
  
  Serial.begin(9600);             // Inicia comunicación serial
  pinMode (relay, OUTPUT);        // Configurar relay como salida
  pinMode(vcc, OUTPUT);           // Pin virtual 11 configurado como salida al sensor de suelo
  pinMode(vcc2, OUTPUT);          // Pin virtual 10 configurado como salida al modulo de relé
  lcd.init();                     // Se inicializa el display LCD
  lcd.backlight();                // Se enciende la luz de fondo de la LCD
  lcd.clear();                    // Limpia los simbolos de la pantalla LCD
  
  }

  
  void loop(){                    // Se ejecuta constantemente (las instrucciones)
 
  V =  analogRead(sensor);        // leer sensor de suelo
  Rsensor = 1024L * Rc / V - Rc;  // Calcular resistencia del sensor del suelo
  Resk = Rsensor / 1000;          // Pasar a kiloohmios

  // Serial.println(contador); Serial.println("  riegos.");                                     // Contador para ver en el monitor serie, cuantas veces se ha regado
  // Serial.print("Valor resistencia: "); Serial.print(Resk); Serial.println(" mil ohmios ");   // Escribir en el monitor serie, el valor de la resistencia
  delay(1000);                                                                                  // Tiempo en actualizarse la LCD

  digitalWrite(vcc, HIGH);      // Habilita el Pin 11
  digitalWrite(vcc2, HIGH);     // Habilita el Pin 10

  lcd.clear();                  // Elimina todos los simbolos de la LCD
  lcd.setCursor(0, 1);          // Se posiciona en la columna 0 y la fila 1
  
  lcd.print(String("Riegos:") + String(contador));    // Imprime el número de riegos 
  int v = (int) Resk;                                 // Pasa a enteros el valor de la resistencia en kohmios
  lcd.setCursor(10, 1);                               // Se posiciona en la columna 10 (a la mitad) y en la fila 1 (fila inferior)
  lcd.print(String("VR:") + String(v));               // Imprime el valor de la resistencia
  lcd.setCursor(0, 0);                                // Posiciona la primera letra despues del segmento 5 en la linea 1
  
  if (Resk > rr){                               // Compara si el valor de la resistencia que se esta midiendo es mayor al valor establecido, en este caso de 10 kohmios
    
  digitalWrite(relay, HIGH);                    // Activar el relay
  lcd.print("Bomba Activa");                    // Imprime en la LCD que la bomba esta activada
  delay(tr * 1000);                             // Espera Tiempo de regado con relay activado
  digitalWrite(relay, LOW);                     // Desactivar relay (apaga la bomba)
  delay(tespera * 1000);                        // Espera Tiempo de espera entre regados con relay desactivado para que el agua se filtre a la tierra y llegue al sensor de suelo
  contador = contador + 1 ;                     // Incrementa en un riego el numero de riegos
    
  }
  
  else{                             // Si la condicion (Resk<rr) no se cumple la bomba no se activa, es decir, que la tierra esta humeda
    
  lcd.print("Bomba Inactiva");      // Imprime bomba inactiva en la LCD
    
  }
  }
