// C++ code
//
int lightState = LOW;
bool isTicking = true;

volatile byte pin2, pin3, pin4 = 0;

const int pirPin = 2;
const int tiltPin = 3;
const int lightPin = 13;

void setup()
{
  Serial.begin(9600);
  
  
  pinMode(pirPin, INPUT);
  pinMode(tiltPin, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);
  
  PCICR |= 0b00000100;
  PCMSK2 |= 0b00011100;
  
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 0.5 Hz increments
  OCR1A = 31249; // = 16000000 / (1024 * 0.5) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

void loop()
{ 
  if (!isTicking)
  {
    digitalWrite(lightPin, pin2);
    digitalWrite(lightPin, pin3);
    digitalWrite(lightPin, pin4);
  }
}

ISR(PCINT2_vect){
  pin2 = PIND & B00000100;
  pin3 = !(PIND & B00001000);
  pin4 = PIND & B00010000;
  
  if(pin2 != LOW) Serial.println("PIR 1 is working.");
  if(pin3 != LOW) Serial.println("Tilt sensor is working.");
  if(pin4 != LOW) Serial.println("PIR 2 is working.");
                                 
  isTicking = false;
}

ISR(TIMER1_COMPA_vect) {
  isTicking = true;
  digitalWrite(lightPin, digitalRead(lightPin) ^ 1);
  
  Serial.println("Clock just ticked");
}