#include <StepDriver.h>

STPDRIVER driver1;

void setup(){
  //Configure Pins (enable, step, direction)
  driver1.pinConfig(2,3,4);

  //Configure Enable Mode
  driver1.enable(HIGH);

  //Define Steps per Rotation
  driver1.stepPerRotation(200);

  //Define Steps per millimeter
  driver1.stepPerMm(100);

  // Setup Acceleration:  acceleration, minimum, maximum
  driver1.motionConfig(20,500,5000);

  //Define Endstop pins and mode (min, max, logic level triggered)
  driver1.endstopConfig(12,13, LOW);

}

void loop(){

  driver1.motorMoveTo(50, HIGH);
  delay(1000);
  driver1.motorMoveTo(50, LOW);
  delay(1000);

}
