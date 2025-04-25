// C++ code
//
int StateLed=LOW;
int StateButtonAfter=LOW;
int StateButtonNow;
void setup()
{
  pinMode(2, INPUT);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  StateButtonNow=digitalRead(2);
  if (StateButtonNow== 1 && StateButtonAfter==LOW){
    StateLed= !StateLed;
    digitalWrite(4, StateLed);
    delay(200);
  }
 StateButtonAfter=StateButtonNow;
  
}
