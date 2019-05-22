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

  // Setup Acceleration:  acceleration value (Must be less than Maximum Speed) , maximum SPEED IN MM/MIN
  driver1.motionConfig(10,10000);

  //Define Endstop pins and mode (min, max, logic level triggered)
  // Not Implemented Yet!
  driver1.endstopConfig(9,9, HIGH);

}

void loop(){
//  Serial.println("Moving 50mm forward then back");
  driver1.motorMoveTo(50, true);

  driver1.motorMoveTo(50, false);


}
