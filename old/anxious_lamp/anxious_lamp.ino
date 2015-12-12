#include <Servo.h>
#include "RunningMedian.h"

// objects
Servo myservo;
RunningMedian samples = RunningMedian(3); // how many samples, lower number = faster

// assign pins to variables
const int proxiPin = 10;
const int solenoidPin = 5;

// sensor values
long pulse;


// range for interaction
int safeZone = 100; // in cm
int offZone = 60; // where light is off and solenoid crazy fast

// time Variables will change:
long previousMillis = 0;        // will store last time Solenoid was fired
long interval = 0;           // interval at which to ploing (milliseconds)


void setup() {
  Serial.begin(9600); // baud rate
  // set pinModes
  myservo.attach(3);
  pinMode(solenoidPin, OUTPUT);
  pinMode(proxiPin, INPUT);
  delay(500);
}
//Main loop where the action takes place
void loop() {
  pulse = pulseIn(proxiPin, HIGH);
  samples.add(pulse);

  float median = samples.getMedian();
  median = median/58;
  Serial.println(median);
  /*
  unsigned long currentMillis = millis();
  if(modE < safeZone && modE >= offZone) {
    Serial.println("in safezone");
    interval = map(modE, safeZone, offZone, 800,300);
    
    Serial.println(interval);
    myservo.write(map(modE, offZone, safeZone, 0, 90)); 
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      ploing(solenoidPin);
    }
   } else if(modE < offZone) {
     Serial.println("offZone");
     interval = 100;
     if(myservo.read() > 0){
       myservo.write(0);
       Serial.println("write servo to 0");
     }
     if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
       ploing(solenoidPin);
     } 
  } else {
     if(myservo.read() < 170){
       myservo.write(170); 
       Serial.println("write servo to 170");
     }
    interval = 1000;
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      ploing(solenoidPin);
    }
  }
  */
} // end loop



