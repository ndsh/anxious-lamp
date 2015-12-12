//#include <Arduino.h>
#include <Servo.h>

class Aktor {
    Servo           servo;            // the servo
    int             pos;              // current servo position 
    int             increment;        // increment to move for each interval
    int             updateInterval;   // interval between updates
    unsigned long   lastUpdate;       // last update of position

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

        void Update(int pos, unsigned long millis) {
            // time to update
            if((millis - lastUpdate) > updateInterval) {
                lastUpdate = millis;
                servo.write(pos);
            }
        }
}; // end public