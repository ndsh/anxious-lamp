#include <Arduino.h> //??? should be able to deal without this

class Rumble {
    int             rumblePin;            // the servo
    unsigned long   lastUpdate;       // last update of position
    int             updateInterval;   // interval between updates

    public: 
        Rumble(int pin, int interval) {
            rumblePin = pin;
            pinMode(rumblePin, OUTPUT);
            updateInterval = interval;
        }

        void Update(int _pos, unsigned long millis) {
            // time to update
            if((millis - lastUpdate) > updateInterval) {
                lastUpdate = millis;
                analogWrite(rumblePin, _pos);
            }
        }
}; // end public
