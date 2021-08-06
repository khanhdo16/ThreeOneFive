// C++ code
//
int lightState = LOW;

const int pirPin = 2;
const int tiltPin = 3;
const int lightPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(tiltPin, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(pirPin), pirToggle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(tiltPin), tiltToggle, CHANGE);
}

void loop()
{
}
                  
void pirToggle() {
  if (digitalRead(pirPin) == HIGH) Serial.println("Motion detected!");
  
  lightState = !lightState;
  digitalWrite(lightPin, lightState);
  
  if (lightState == HIGH) Serial.println("Light on!");
}

void tiltToggle() {
  if (digitalRead(tiltPin) == LOW) Serial.println("Tilt detected!");
  
  lightState = !lightState;
  digitalWrite(lightPin, lightState);
  
  if (lightState == HIGH) Serial.println("Light on!");

}