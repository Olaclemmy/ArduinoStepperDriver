#include <StepperDriver.h>

//Create Instance and Assign Pins (int stp, int dir, int ena, int enaval, int emin, int emax, bool limitval, double stepsPerMM, int stepsPerRotation, int acceleration, int maxSpeed)
STPDRIVER driver1(
  2,    // Step Pin
  5,    // Dir Pin
  8,    // Enable Pin
  LOW,  // Enable Active (LOW/HIGH)
  9,    // Min Endstop
  9,    // Max Endstop
  HIGH, // Endstops trigger when
  200,  // Steps per mm
  3200, // Steps per Rotation
  100,  // Acceleration Value
  5000  // Maximum Speed (mm/min)
);

void setup(){
  Serial.begin(115200);
}

void loop(){
  driver1.enable();
  //Moving 50mm forward then back
  driver1.motorMove(50, 5000);
  driver1.motorMove(-50, 5000);

  // spin 10 rotations one way then 10 rotations back
  driver1.motorMoveRotations(5, 5000);
  driver1.motorMoveRotations(-5, 5000);
  driver1.disable();
  delay(500);

}
