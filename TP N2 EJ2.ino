struct Led {
  int pin;
  bool estado; 
};

Led leds[] = {
  {0, false},
  {1, false},
  {2, false},
  {3, false}
};

const int cantidadLeds = sizeof(leds) / sizeof(leds[0]);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < cantidadLeds; i++) {
    pinMode(leds[i].pin, OUTPUT);
    digitalWrite(leds[i].pin, LOW);  // Inicialmente apagados
  }
}

void loop() {
  // Ejemplo: encender y apagar en secuencia
  for (int i = 0; i < cantidadLeds; i++) {
    if (i ==0) {
    prenderLed(i);
    delay(5000);
    apagarLed(i);
    delay(5000);
    }
    if (i ==1) {
    prenderLed(i);
    delay(10000);
    apagarLed(i);
    delay(10000);
    }
    if (i ==2) {
    prenderLed(i);
    delay(1000);
    apagarLed(i);
    delay(1000);
    }
    if (i ==3) {
    prenderLed(i);
    delay(15000);
    apagarLed(i);
    delay(15000);
    }
  }
}

// Funciones para manejar LEDs
void prenderLed(int index) {
  leds[index].estado = true;
  digitalWrite(leds[index].pin, leds[index].estado);
  Serial.print("LED en pin ");
  Serial.print(leds[index].pin);
  Serial.println(" encendido");
}

void apagarLed(int index) {
  leds[index].estado = false;
  digitalWrite(leds[index].pin, leds[index].estado);
  Serial.print("LED en pin ");
  Serial.print(leds[index].pin);
  Serial.println(" apagado");
}

void negarLed(int index) {
  leds[index].estado = !leds[index].estado;
  digitalWrite(leds[index].pin, leds[index].estado);
  Serial.print("LED en pin ");
  Serial.print(leds[index].pin);
  Serial.println(" negado");
}
