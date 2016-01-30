//#include <Arduino.h> ??? should be able to deal without this
#include "SoftwareServo.h" 

class Aktor {
    SoftwareServo   servo;            // the servo
    int             pos;              // current servo position 
    int             increment;        // increment to move for each interval
    int             updateInterval;   // interval between updates
    unsigned long   lastUpdate;       // last update of position
    int             maximum;          // maximum position of servo

    public: 
        Aktor(int interval) {
            updateInterval = interval;            
        }

        void Attach(int pin) {
            servo.attach(pin);
        }

        void Detach() {
            servo.detach();
        }

        void Update(int _pos, unsigned long millis) {
            // time to update
            if((millis - lastUpdate) > updateInterval) {
                lastUpdate = millis;
                servo.write(_pos);
                SoftwareServo::refresh();
            }
        }
}; // end public
