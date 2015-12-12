#include "RunningMedian.h"
#include <Servo.h>


// objects
RunningMedian samples = RunningMedian(3); // how many samples, lower number = faster
Servo myservo;


// assign pins to variables
const int proxiPin = 10;
const int solenoidPin = 5;

// sensor values
long pulse;

// range for interaction
float zone_anxiety = 70; // in cm
float zone_panic = 30; // where light is off and solenoid crazy fast

// time Variables will change:
long previousMillis = 0;        // will store last time Solenoid was fired
long interval_normal = 1000;           // interval at which to ploing (milliseconds)
long interval_anxious = 100;           // interval at which to ploing (milliseconds)

/*
 * 1000 = normal
 * 100 = anxious
 */



void setup() {
  Serial.begin(9600); // baud rate, communication with computer over USB
  // set pinModes
  pinMode(proxiPin, INPUT);
   pinMode(solenoidPin, OUTPUT);
   myservo.attach(3);
  delay(500);
}
//Main loop where the action takes place
void loop() {
  unsigned long currentMillis = millis();
  pulse = pulseIn(proxiPin, HIGH);
  samples.add(pulse);

  float median = samples.getMedian();
  median = median/58; // conversion to cm, approximation

  if(median <= zone_panic) {
     myservo.write(10);
     if(currentMillis - previousMillis > interval_anxious) {
      previousMillis = currentMillis;
      ploing(solenoidPin);
    }
  } else if(median <= zone_anxiety) {
    float fadeIn = map(median, zone_panic, zone_anxiety, interval_anxious, interval_normal);
    myservo.write(90);
    if(currentMillis - previousMillis > fadeIn) {
      previousMillis = currentMillis;
      ploing(solenoidPin);
    }
  } else { 
    myservo.write(180);
  }

    
} // end loop

void ploing(int pin) {
  digitalWrite(pin, LOW);
  delay(40);
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}

