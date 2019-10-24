#include <Servo.h>

// Motor Tilt and Pan Function 
// Ben Dean
// 10/15/2019

Servo tiltServo; // Defines the tilt servo
Servo panServo; // Defines the pan servo

const int tiltServoPin = 9; // Pin 9 is picked because I read that the servo library only works on 9 or 10
const int panServoPin = 10; // Pin 10 is picked because I read that the servo library only works on 9 or 10

//Global Calibrations
const int tiltCal = 10; // This is the number of tilt angles point and thus the number of rows of the matrix
const int panCal = 360; // This is the number of pan angle points and thus the number of columns of the matrix

int currentMatrix[tiltCal][panCal]; // This is the current matrix 

//Test Variable, This should be deleted when added to the whole file
const int testLedPin = 13;
int testMeasurementValue = 0;

void setup() {
  // put your setup code here, to run once:
  tiltServo.attach(tiltServoPin); // sets up the tilt servo on the tilt servo pin
  panServo.attach(panServoPin); // sets up the pan servo on the pan servo pin
}

int measurementFunction(){
  // This is Tirath's function but I have it as a test function that lights a LED to show that its doing this
  digitalWrite(testLedPin, HIGH);
  delay(2000);
  digitalWrite(testLedPin, LOW);
  testMeasurementValue = testMeasurementValue ++;
  return testMeasurementValue;
}

void roomMap() {
  // This function maps the room by filling a matrix with measurements
   
  // These are used because the servo library are used
  // These are both calibrations based on the base design
  const int tiltHighMap = 30; // This is the high tilt angle the servo needs to position above the "level" position
  const int tiltLowMap = 0; //This is the angle the servo needs to be at to position the sensor at the "level" position
  const int panHighMap = 360; // This is the angle the pan motor ends at
  const int panLowMap = 0; // This is the angle the pan motor starts at
  const int resetDelayTime = 50; // This is the time to resist the sensor to the zero position
  const int tiltDelayTime = 15; // This is the time for the tilt servo to move
  const int panDelayTime = 15; // This is the time for the pan servo to move


  // resets the sensor to the zero position
  tiltServo.write(tiltLowMap);
  panServo.write(panLowMap);
  delay(resetDelayTime);

  // rotates the base to pan the room, then tilt the sensor, and repetes
  // tilt defines which tilt position we are at
  // pan defines which pan position we are at
  for( int tilt = 0; tilt <= tiltCal; tilt ++){
    // adjust the tilt angle
     int tiltAngle = map( tilt, 0, tiltCal, tiltLowMap, tiltHighMap); // remaps the tilt column value to a tilt angle for the servo functionality
     tiltServo.write(tiltAngle); // moves the servo to the new angle 
     delay(tiltDelayTime); //Allow time for the servo to tilt

    for( int pan = 0; pan <= panCal; pan ++){
      // adjust the pan angle
      // setup for servo motor but I don't think we will end up using one for the pan
      int panAngle = map( pan, 0, panCal, panLowMap, panHighMap);
      panServo.write(panAngle);
      delay(panDelayTime);

      //call the measurement function and record the value in the matrix
      currentMatrix[tilt][pan] = measurementFunction();
      return;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  roomMap();
}
