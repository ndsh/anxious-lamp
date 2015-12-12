#include <Servo.h>

// objects
Servo myservo;

void setup() {
  Serial.begin(9600); // baud rate
  // set pinModes
  myservo.attach(3);
  delay(500);
}
//Main loop where the action takes place
void loop() {
  myservo.write(180);
  delay(1000);
  myservo.write(0);
  delay(1000);
} // end loop



