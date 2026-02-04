# V-metro-Proyecto-
// Definición de pines para los LEDs
const int ledVerde1 = 4;
const int ledVerde2 = 5;
const int ledAmarillo1 = 6;
const int ledAmarillo2 = 7;
const int ledNaranja1 = 8;
const int ledNaranja2 = 9;
const int ledRojo1 = 10;
const int ledRojo2 = 11;

// Definición de pines para el pulsador y el micrófono
const int pinPulsador = 12;
const int pinMicrofono = A0; // Salida de envolvente del MAX9814

// Variables para el control del tiempo y el estado
unsigned long ultimoTiempoActualizacion = 0;
const long intervaloActualizacion = 100; // Actualizar la lectura cada 100ms

void setup() {
  // Configurar todos los pines de los LEDs como SALIDAS
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledAmarillo1, OUTPUT);
  pinMode(ledAmarillo2, OUTPUT);
  pinMode(ledNaranja1, OUTPUT);
  pinMode(ledNaranja2, OUTPUT);
  pinMode(ledRojo1, OUTPUT);
  pinMode(ledRojo2, OUTPUT);

  // Configurar el pin del pulsador como ENTRADA
  pinMode(pinPulsador, INPUT);
  
  // Inicializar la comunicación serie para depuración (opcional)
  Serial.begin(9600);
}

void loop() {
  unsigned long tiempoActual = millis();

  // Comprobar si se ha presionado el pulsador para la prueba de LEDs
  if (digitalRead(pinPulsador) == HIGH) {
    pruebaLeds();
    return; // Sale del loop para no medir sonido mientras se prueba
  }

  // Actualizar la lectura del sonido solo cada 'intervaloActualizacion' milisegundos
  if (tiempoActual - ultimoTiempoActualizacion >= intervaloActualizacion) {
    ultimoTiempoActualizacion = tiempoActual;

    // 1. Leer el valor de la salida de envolvente del MAX9814 (0-1023)
    // Esta salida ya es un valor de CC que representa el nivel de sonido pico.
    int valorSensor = analogRead(pinMicrofono);

    // 2. Mapear el valor del sensor a la escala de dB deseada (20-60)
    // El MAX9814 da un rango amplio, por lo que mapear a 20-60 dB es ideal.
    int nivelDb = map(valorSensor, 0, 1023, 20, 60);
    
    // Imprimir el valor en el Monitor Serie para calibrar y verlo
    Serial.print("Valor Sensor: ");
    Serial.print(valorSensor);
    Serial.print(" -> Nivel dB simulado: ");
    Serial.println(nivelDb);

    // 3. Actualizar los LEDs según el nivel de sonido
    actualizarLeds(nivelDb);
  }
}

// Función para encender los LEDs según el nivel de dB (RANGO 20-60)
void actualizarLeds(int nivel) {
  // Primero, apagar todos los LEDs
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledNaranja1, LOW);
  digitalWrite(ledNaranja2, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);

  // Encender LEDs según el nivel de sonido
  if (nivel >= 20) digitalWrite(ledVerde1, HIGH);   // 20 dB
  if (nivel >= 25) digitalWrite(ledVerde2, HIGH);   // 25 dB
  if (nivel >= 30) digitalWrite(ledAmarillo1, HIGH); // 30 dB
  if (nivel >= 35) digitalWrite(ledAmarillo2, HIGH); // 35 dB
  if (nivel >= 40) digitalWrite(ledNaranja1, HIGH);  // 40 dB
  if (nivel >= 45) digitalWrite(ledNaranja2, HIGH);  // 45 dB
  if (nivel >= 50) digitalWrite(ledRojo1, HIGH);   // 50 dB
  if (nivel >= 60) digitalWrite(ledRojo2, HIGH);   // 60 dB
}

// Función para probar todos los LEDs
void pruebaLeds() {
  
  Serial.print("Probar Led\n");
  
  // Encender todos los LEDs
  digitalWrite(ledVerde1, HIGH);
  digitalWrite(ledVerde2, HIGH);
  digitalWrite(ledAmarillo1, HIGH);
  digitalWrite(ledAmarillo2, HIGH);
  digitalWrite(ledNaranja1, HIGH);
  digitalWrite(ledNaranja2, HIGH);
  digitalWrite(ledRojo1, HIGH);
  digitalWrite(ledRojo2, HIGH);
  
  delay(1000); // Mantenerlos encendidos por 1 segundo

  // Apagar todos los LEDs
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledNaranja1, LOW);
  digitalWrite(ledNaranja2, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);
  
  delay(1000); // Mantenerlos encendidos por 1 segundo
}
