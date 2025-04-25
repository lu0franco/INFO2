// C++ code
//
int StateLed=LOW;
int StateButtonAfter=LOW;
int StateButtonNow;
unsigned long previousMillis = 0;  
const long interval = 60000;
void setup()
{
  pinMode(2, INPUT);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  StateButtonNow=digitalRead(2);
  if (StateButtonNow==1) {      
    StateLed= !StateLed;
    delay(100);
     digitalWrite(4, StateLed);}
    if (currentMillis - previousMillis >= interval && StateLed== 1) {
    previousMillis = currentMillis;
      StateLed= !StateLed;
      digitalWrite(4, StateLed);
    }
}
