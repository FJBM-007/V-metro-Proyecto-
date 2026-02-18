// --- DEFINICIÓN DE PINES ---
const int ledVerde1 = 4;
const int ledVerde2 = 5;
const int ledAmarillo1 = 6;
const int ledAmarillo2 = 7;
const int ledNaranja1 = 8;
const int ledNaranja2 = 9;
const int ledRojo1 = 10;
const int ledRojo2 = 11;

const int pinPulsador = 12;
const int pinMicrofono = A0; 

// --- VARIABLES ---
const int sampleWindow = 250; // Ventana de muestra en ms (50ms = 20Hz)
unsigned int sample;

void setup() {
  // Configurar LEDs
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledAmarillo1, OUTPUT);
  pinMode(ledAmarillo2, OUTPUT);
  pinMode(ledNaranja1, OUTPUT);
  pinMode(ledNaranja2, OUTPUT);
  pinMode(ledRojo1, OUTPUT);
  pinMode(ledRojo2, OUTPUT);

  // Configurar Pulsador
  pinMode(pinPulsador, INPUT); // Asegúrate de tener una resistencia Pulldown o usa INPUT_PULLUP
  
  Serial.begin(9600);
}

void loop() {
  // 1. Verificar botón de prueba
  if (digitalRead(pinPulsador) == HIGH) {
    pruebaLeds();
    return; 
  }

  // 2. MEDICIÓN DE SONIDO (Algoritmo Pico a Pico)
  unsigned long startMillis = millis(); 
  unsigned int peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // Recolectar datos durante 50ms
  while (millis() - startMillis < sampleWindow) {
      sample = analogRead(pinMicrofono);
      if (sample < 1024) {
          if (sample > signalMax) {
             signalMax = sample; 
          }
          else if (sample < signalMin) {
             signalMin = sample; 
          }
      }
  }
  
  peakToPeak = signalMax - signalMin;  // Amplitud de la onda
  
  // Convertir a Voltios (aprox) para depuración
  double volts = (peakToPeak * 5.0) / 1024; 
  
  // Imprimir para calibrar
  Serial.print("Volts: ");
  Serial.print(volts);
  Serial.print(" | Lectura Raw: ");
  Serial.println(peakToPeak);

  // 3. ACTUALIZAR LEDS
  // Nota: Debes ajustar estos valores "Raw" según tu ruido ambiente.
  // He puesto valores estimados para un micrófono electret estándar.
  actualizarLeds(peakToPeak);
}

// Función corregida para usar la lectura Pico a Pico (0 a 1023)
void actualizarLeds(int lecturaRaw) {
  // Apagar todo primero
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledNaranja1, LOW);
  digitalWrite(ledNaranja2, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);

  // Umbrales basados en la amplitud de la onda (ajustar experimentalmente)
  // Un susurro puede ser 20-50, hablar normal 100-300, gritar > 500
  if (lecturaRaw >= 30) digitalWrite(ledVerde1, HIGH);   
  if (lecturaRaw >= 80) digitalWrite(ledVerde2, HIGH);   
  if (lecturaRaw >= 150) digitalWrite(ledAmarillo1, HIGH); 
  if (lecturaRaw >= 250) digitalWrite(ledAmarillo2, HIGH); 
  if (lecturaRaw >= 400) digitalWrite(ledNaranja1, HIGH);  
  if (lecturaRaw >= 600) digitalWrite(ledNaranja2, HIGH);  
  if (lecturaRaw >= 800) digitalWrite(ledRojo1, HIGH);   
  if (lecturaRaw >= 950) digitalWrite(ledRojo2, HIGH);   
}

void pruebaLeds() {
  Serial.println("--- TEST DE LEDS ---");
  // Encender todos
  digitalWrite(ledVerde1, HIGH);
  digitalWrite(ledVerde2, HIGH);
  digitalWrite(ledAmarillo1, HIGH);
  digitalWrite(ledAmarillo2, HIGH);
  digitalWrite(ledNaranja1, HIGH);
  digitalWrite(ledNaranja2, HIGH);
  digitalWrite(ledRojo1, HIGH);
  digitalWrite(ledRojo2, HIGH);
  delay(1000);
  
  // Apagar todos
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledNaranja1, LOW);
  digitalWrite(ledNaranja2, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);
  delay(500);
}