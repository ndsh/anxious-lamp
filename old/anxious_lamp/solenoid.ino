  void ploing(int pin) {
    //Serial.println("itsa ping");
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
    delay(40);              // wait for a second
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(10);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  }
