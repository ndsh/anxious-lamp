#include "RunningMedian.h"

// objects
RunningMedian samples = RunningMedian(3); // how many samples, lower number = faster

// assign pins to variables
const int proxiPin = 10;

// sensor values
long pulse;


void setup() {
  Serial.begin(9600); // baud rate, communication with computer over USB
  // set pinModes
  pinMode(proxiPin, INPUT);
  delay(500);
}
//Main loop where the action takes place
void loop() {
  pulse = pulseIn(proxiPin, HIGH);
  samples.add(pulse);

  float median = samples.getMedian();
  median = median/58; // conversion to cm
  Serial.println(median);
} // end loop



