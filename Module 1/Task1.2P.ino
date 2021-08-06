// C++ code
//
int buzzerState = LOW;

const int pirPin = 2;
const int buzzerPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(pirPin), buzz, CHANGE);
}

void loop()
{
  
}
                  
void buzz() {
  if (digitalRead(pirPin) == HIGH) Serial.println("Motion detected!");
  
  buzzerState = !buzzerState;
  
  digitalWrite(buzzerPin, buzzerState);
  
  if (buzzerState == HIGH) Serial.println("Buzzer buzzed!");
}
