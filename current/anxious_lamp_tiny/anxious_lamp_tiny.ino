#include "RunningMedian.h"
#include "SoftwareServo.h" 
#include "aktor.cpp"
#include "flasher.cpp"


//#define DEBUG


// assign pins to variables
#ifdef DEBUG
#include "SoftwareSerial.h"
const int servoPin = 8; // 3 on uno / on tiny… vorrübergehend: 6 auf FRITZING: 8 
const int mosfetPin = 4; // 5 on uno / 5 on tiny
const int proxiPin = 5; // 10 on uno / 3 on tiny

const int Rx = 7; // this is physical pin 6
const int Tx = 6; // this is physical pin 7
SoftwareSerial mySerial(Rx, Tx);
#else
  const int servoPin = 6; // 3 on uno / on tiny… vorrübergehend: 6 auf FRITZING: 8 
  const int mosfetPin = 5; // 5 on uno / 5 on tiny
  const int proxiPin = 7; // 10 on uno / 3 on tiny
#endif

int maxAngle = 170;
int restingCounter = 0;
int stepsToRest = 6;


// objects
RunningMedian samples = RunningMedian(11); // how many samples, lower number = faster
Aktor aktor(15);
Flasher mosfet(mosfetPin, 200, 200);

// sensor values
long pulse;

// range for interaction
float zone_anxiety = 90; // in cm
float zone_panic = 40; // where light is off and solenoid crazy fast

// time Variable will change:
long previousMillis = 0;        // will store last time Solenoid was fired

long interval_normal = 500;           // interval at which to ploing (milliseconds)
long interval_anxious = 50;           // interval at which to ploing (milliseconds)

/*
 * 1000 = normal
 * 100 = anxious
 */

long previousValue = 0; // for metafilter



void setup() {

    #ifdef DEBUG
      // set pinModes
      pinMode(Rx, INPUT);
      pinMode(Tx, OUTPUT);
      mySerial.begin(9600);
    #endif

    pinMode(proxiPin, INPUT); // activate PULLUP? need to test
    pinMode(mosfetPin, OUTPUT);
    aktor.Attach(servoPin);
    delay(500);
}

// main loop where the action takes place
void loop() {
    unsigned long currentMillis = millis();
    pulse = pulseIn(proxiPin, HIGH, 30000);
    samples.add(pulse);

    float median = samples.getMedian();
    median = median/58; // conversion to cm, approximation
    //mySerial.println(median);
    //Serial.println(median);

    // metafilter hier
    // special case, if a low value follows a high value
    if(median > previousValue) {
      
        if(median <= zone_panic) 
        {
            restingCounter = 0;
            mosfet.Go();
            //Serial.println("## (panic zone): ");
             aktor.Update(0, millis());
             if( (currentMillis - previousMillis) > interval_anxious) {
                previousMillis = currentMillis;
                // ploing(mosfetPin);
                mosfet.Update();
            }

        } else if(median <= zone_anxiety) 
        {
            restingCounter = 0;
            mosfet.Go();
            //Serial.println("## (anxiety zone): ");
            float fadeIn = map(median, zone_panic, zone_anxiety, interval_anxious, interval_normal);
            float angleIn = map(median, zone_panic, zone_anxiety, 30, maxAngle);

            for(int i = angleIn; i<maxAngle; i++) {
                aktor.Update(i, millis());
            }
            for(int i = maxAngle; i>=angleIn; i--) {
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
            if(restingCounter < stepsToRest) {
             aktor.Update(maxAngle, millis());
             restingCounter++;
            }
         
        }
    }
    previousValue = median;
} // end loop


