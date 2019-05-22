#include <StepperDriver.h>

STPDRIVER driver1;

void setup(){

  Serial.begin(115200);
  //Configure Pins (enable, step, direction)
  driver1.pinConfig(8,2,5);

  //Configure Enable Mode
  driver1.enable(HIGH);

  //Define Steps per Rotation
  driver1.stepPerRotation(200);

  //Define Steps per millimeter
  driver1.stepPerMm(100);

  // Setup Acceleration:  acceleration , maximum SPEED IN MM/MIN
  driver1.motionConfig(10,5000);

  //Define Endstop pins and mode (min, max, logic level triggered)
  driver1.endstopConfig(9,9, HIGH);

}

void loop(){
  //Moving 50mm forward then back
  driver1.motorMoveTo(50, true);
  driver1.motorMoveTo(50, false);

  // spin 10 rotations one way then 10 rotations back
  driver1.motorMoveRotations(10, true, 2000);
  driver1.motorMoveRotations(10, false, 5000);


}
