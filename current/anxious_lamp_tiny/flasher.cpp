#include <Arduino.h>
class Flasher {
	// this class can handle "things" like LEDs or anything connected to a MOSFET (motor, solenoid)
	int flasherPin;      // the number of the LED pin
	long OnTime;     // milliseconds of on-time
	long OffTime;    // milliseconds of off-time
 
	// These maintain the current state
	int flasherState;             		// flasherState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
	bool running = false;
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
    Flasher(int pin, long on, long off) {
	    flasherPin = pin;
	    pinMode(flasherPin, OUTPUT);     
	  
	    OnTime = on;
	    OffTime = off;
	
	    flasherState = LOW; 
	    previousMillis = 0;
  }
 
  void Update() {
  	if(running) {
	    // check to see if it's time to change the state of the LED
	    unsigned long currentMillis = millis();
	     
	    if((flasherState == HIGH) && (currentMillis - previousMillis >= OnTime))
	    {
	    	flasherState = LOW;  // Turn it off
	      previousMillis = currentMillis;  // Remember the time
	      digitalWrite(flasherPin, flasherState);  // Update the actual LED
	    }
	    else if ((flasherState == LOW) && (currentMillis - previousMillis >= OffTime))
	    {
	      flasherState = HIGH;  // turn it on
	      previousMillis = currentMillis;   // Remember the time
	      digitalWrite(flasherPin, flasherState);	  // Update the actual LED
	    }
    } else {
    	digitalWrite(flasherPin, LOW);
    }
  }

  void Go() 
  {
  	running = true;
  }

  void Stop()
  {
  	running = false;
  }
};
