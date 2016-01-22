#include "RunningMedian.h"
#include <Servo.h>
#include "aktor.cpp"
#include "flasher.cpp"

// assign pins to variables
const int servoPin = 3;
const int mosfetPin = 5;
const int proxiPin = 10;


// objects
RunningMedian samples = RunningMedian(23); // how many samples, lower number = faster
Aktor aktor(15);
Flasher mosfet(mosfetPin, 20, 20);

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

long previousValue = 0; // for metafilter



void setup() {
    Serial.begin(9600); // baud rate, communication with computer over USB
    // set pinModes
    pinMode(proxiPin, INPUT); // activate PULLUP? need to test
    pinMode(mosfetPin, OUTPUT);
    aktor.Attach(servoPin);
    delay(500);
}

// main loop where the action takes place
void loop() {
    unsigned long currentMillis = millis();
    pulse = pulseIn(proxiPin, HIGH);
    samples.add(pulse);

    float median = samples.getMedian();
    median = median/58; // conversion to cm, approximation
    Serial.println(median);

    // metafilter hier
    // special case, if a low value follows a high value
    if(median > previousValue) {


        if(median <= zone_panic) 
        {
            mosfet.Go();
            Serial.println("## (panic zone): ");
             aktor.Update(0, millis());
             if( (currentMillis - previousMillis) > interval_anxious) {
                previousMillis = currentMillis;
                // ploing(mosfetPin);
                mosfet.Update();
            }

        } else if(median <= zone_anxiety) 
        {
            mosfet.Go();
            Serial.println("## (anxiety zone): ");
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
                // ploing(mosfetPin);
                mosfet.Update();
            }
        } else 
        { 
            mosfet.Stop();
            mosfet.Update();
            Serial.println("## (all is cool zone): ");
            aktor.Update(180, millis());
        }
    }
    previousValue = median;
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

