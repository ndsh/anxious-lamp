// assign pins to variables
const int solenoidPin = 5;

// time Variables will change:
long previousMillis = 0;        // will store last time Solenoid was fired
long interval_normal = 1000;           // interval at which to ploing (milliseconds)
long interval_anxious = 100;           // interval at which to ploing (milliseconds)
long interval_energize = 10;           // how much millis to energize the coil

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
    ploing(solenoidPin, currentMillis );
  } 
} // end loop

void ploing(int pin, long previousMillis) {
  long currentMillis = 0;
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);

}
