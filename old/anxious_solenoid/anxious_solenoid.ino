// assign pins to variables
const int solenoidPin = 5;

// time Variables will change:
long previousMillis = 0;        // will store last time Solenoid was fired
long interval_normal = 1000;           // interval at which to ploing (milliseconds)
long interval_anxious = 100;           // interval at which to ploing (milliseconds)

/*
 * 1000 = normal
 * 100 = anxious
 */

void setup() {
  Serial.begin(9600); // baud rate
  // set pinModes
  pinMode(solenoidPin, OUTPUT);
  
  delay(500);
}
//Main loop where the action takes place
void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval_normal) {
    previousMillis = currentMillis;
    ploing(solenoidPin);
  } 
} // end loop

void ploing(int pin) {
  digitalWrite(pin, LOW);
  delay(40);
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}
