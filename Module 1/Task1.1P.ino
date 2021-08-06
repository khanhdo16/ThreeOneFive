// C++ code
//
int pirValue = LOW;
int buzzerState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  pirValue = digitalRead(2);
  Serial.println("PIR " + String(pirValue));
  
  if(pirValue == HIGH) {
    Serial.println("Motion detected!");
    
    buzzerState = HIGH;
    digitalWrite(13, HIGH);
    delay(1000);
  }
  else {
    Serial.println("No motion detected!");
    
    digitalWrite(13, LOW);
    buzzerState = LOW;
    delay(1000);
  }
  Serial.println("Buzzer " + String(buzzerState));
}