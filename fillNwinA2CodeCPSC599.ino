// maham fatima
// cpsc 599 A2
// fill n win
// Nov 6 2024

#include <Servo.h>
// REFERENCES:
// servo code is adapted from sweep example: (https://docs.arduino.cc/learn/electronics/servo-motors/)
// code about joystick button is adapted from: https://42bots.com/tutorials/arduino-joystick-module-example/
// ultrasonic code adapted from : https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/

// set up servo, joystick and ultrasonic sensor
Servo servoFlap;      // servo to release the items into jar
Servo servoSurprise;  // servo to open the door to the prizes

int pos = 0;          // set posistion of the servo for the moving mechanism 
bool surpriseBoxOpen = false;
// set up pins
const int buttonPin = 12; // set the button on the joystick (sw) as pin 12

const int trigPin = 3;     // set the ultrasonic trig pin to pin 3
const int echoPin = 2 ;    // set the ultrasonic echo pin to pin 2

void setup(){
  Serial.begin(9600);

  servoFlap.attach(9);    // set the flap pin for controlling the flow of material to pin 9
  servoSurprise.attach(10);    // set the flap pin for controlling the surprise box to pin 10
  
  // code about joystick button is adapted from: https://42bots.com/tutorials/arduino-joystick-module-example/
  // code about ultrasonic is adapeted from: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, OUTPUT);

  servoSurprise.write(0);   // set surprise box initial position as 0 to make sure it resets and chance to put surprise in if no chickpea yet. 

}

void loop(){

  // code about joystick button is adapted from: https://42bots.com/tutorials/arduino-joystick-module-example/
  // loop and check if button is pressed 
  if (digitalRead(buttonPin) == LOW) {
   // Serial.println("BUTTON IS PRESSED"); // for testing only

   for (pos =20; pos <= 70; pos +=1) {
    servoFlap.write(pos);
    delay(15);
   }
   for (pos = 70; pos >= 20; pos -=1) {
    servoFlap.write(pos);
    delay(5);
   }
   
  }

  // code about ultrasonic is adapeted from: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
  // loop and check the ultrasonic distance to detect when the jar is about to be full as a result of the bottle being empty

  long duration;
  float distanceCM; 
  digitalWrite(trigPin, LOW);   // to ensure clean high pulse next reset it with initial low 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);        // set high for 10 ms
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // read echo pin
  distanceCM = (duration *0.0343) / 2; // distance in cm 
  // Serial.println(distanceCM); // for testing only

  const float emptyDistance = 14.0;   // i played around with the numbers until i reached one that indicated the bottle was empty

  if (distanceCM > emptyDistance && !surpriseBoxOpen){
    servoSurprise.write(0);   // move surprise boc servo
    delay(1000);
    surpriseBoxOpen = true;           // set box as open 

  }else if (distanceCM < emptyDistance && surpriseBoxOpen){
    servoSurprise.write(90);          // move surprise box servo
    surpriseBoxOpen = false;           // set box as open false
  }
  delay(1000);

}
