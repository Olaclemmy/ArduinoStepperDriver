#include "STPDRIVER.h"

STPDRIVER::STPDRIVER(){
}

void STPDRIVER::pinConfig(int ena, int stp, int dir){

    ENA = ena;			//Enable Pin
    STP = stp;			//Step Pin
    DIR = dir;      //Dir Pin

	  //Define PinModes
    pinMode(ENA, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(STP, OUTPUT);
}


void STPDRIVER::enable(bool state)
{
	digitalWrite(ENA, !state);// Activates and deactivates the STPDRIVER chip (FALSE = active, TRUE = deactivates)
	delay (10);               // Delay 10 milliseconds
}

void STPDRIVER::stepPerMm(double steps)
{
	SPM = steps;
}

void STPDRIVER::stepPerRotation(int steps)
{
	SPR = steps;
}

void STPDRIVER::endstopConfig(int emin, int emax, bool level)
{
	EMAX = emax;
	EMIN = emin;
	LVL  = level;
	pinMode(EMAX, INPUT);
	pinMode(EMIN, INPUT);
}


void STPDRIVER::motionConfig(int acceleration, int maxSpeed){
	ACC = acceleration;
	MAXSPEED = maxSpeed;
}



void STPDRIVER::motorMove(bool direction) // Move 1 step in Direction
{
	digitalWrite(DIR, direction);
  long pulseDelay = 1/(MAXSPEED/1000000) ;
  Serial.print("Setting Max Speed to ");
  Serial.print(MAXSPEED);
  Serial.print(" which is a minimum step pulse of ");
  Serial.println(pulseDelay);
	digitalWrite(STP, HIGH);
	delayMicroseconds(pulseDelay/2);
	digitalWrite(STP, LOW);
	delayMicroseconds(pulseDelay/2);

}

void STPDRIVER::motorMoveTo(double distance, bool direction) // Move distance in mm, in direction
{
	digitalWrite(DIR, direction);

  int slowestPulse = 5000; // Start with a long pulse
  long fastestPulse = 1/(((MAXSPEED/60)*SPM)/1000000) ;
  int pulseLength = slowestPulse; // Start with a long pulse
  int numOfPulsesToSpeed = (slowestPulse-fastestPulse) / ACC;

  // Serial.print("Setting Max Speed to ");
  // Serial.print(MAXSPEED);
  // Serial.print(" which is a minimum step pulse of ");
  // Serial.print(fastestPulse);
  // Serial.print(" accel/decel over ");
  // Serial.print(numOfPulsesToSpeed);
  // Serial.println(" steps");
  // Run the move
	for(long i = 0; i < distance*SPM; i++){

    // Serial.println(pulseLength);
    // Start Accelerating
    if (i < (distance*SPM)/2) {
      // first half of travel
      if (i < numOfPulsesToSpeed) {
        // Serial.println(pulseLength);
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
          pulseLength = pulseLength - ACC;
      } else {
        // just coasting along...
        // Serial.println(pulseLength);
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
      }
    } else {
      if (i > ((distance*SPM)-numOfPulsesToSpeed)) {
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
        pulseLength = pulseLength + ACC;
      } else {
        // just coasting along...
        // Serial.println(pulseLength);
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
      }
    }
	}
}

void STPDRIVER::motorMoveRotations(int rounds, bool direction, int speed)	// move rotations, in direction
{
	digitalWrite(DIR, direction);
  long fastestPulse = 1/(((speed/60)*SPM)/1000000) ;
	for(int r = 0; r < rounds; r++){
		for(int i = 0; i < SPR; i++){
				digitalWrite(STP, HIGH);
				delayMicroseconds(fastestPulse/2);
				digitalWrite(STP, LOW);
				delayMicroseconds(fastestPulse/2);
		}
	}
}
