#include "RunningMedian.h"
#include <Servo.h>
#include "aktor.cpp"

// objects
RunningMedian samples = RunningMedian(3); // how many samples, lower number = faster
Aktor aktor(15);


// assign pins to variables
const int proxiPin = 10;
const int solenoidPin = 5;

// sensor values
long pulse;

// range for interaction
float zone_anxiety = 70; // in cm
float zone_panic = 30; // where light is off and solenoid crazy fast

// time Variable will change:
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
    pinMode(proxiPin, INPUT); // activate PULLUP? need to test
    pinMode(solenoidPin, OUTPUT);
    aktor.Attach(3);
    delay(500);
}

// main loop where the action takes place
void loop() {
    unsigned long currentMillis = millis();
    pulse = pulseIn(proxiPin, HIGH);
    samples.add(pulse);

    float median = samples.getMedian();
    median = median/58; // conversion to cm, approximation

    if(median <= zone_panic) 
    {
         aktor.Update(0, millis());
         if( (currentMillis - previousMillis) > interval_anxious) {
            previousMillis = currentMillis;
            ploing(solenoidPin);
        }
    } else if(median <= zone_anxiety) 
    {
        float fadeIn = map(median, zone_panic, zone_anxiety, interval_anxious, interval_normal);
        float angleIn = map(median, zone_panic, zone_anxiety, 30, 180);

        for(int i = angleIn; i<180; i++) {
            aktor.Update(i, millis());
        }
        for(int i = 180; i>=angleIn; i--) {
            aktor.Update(i, millis());
        }
        if( (currentMillis - previousMillis) > fadeIn) {
            previousMillis = currentMillis;
            ploing(solenoidPin);
        }
    } else 
    { 
        aktor.Update(180, millis());
    }
} // end loop

void ploing(int pin) {
    digitalWrite(pin, LOW);
    delay(40);
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
}

void heartBeat(int pin)  {
    ploing(pin);
    ploing(pin);
}

