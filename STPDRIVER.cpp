#include "STPDRIVER.h"


STPDRIVER::STPDRIVER(int stp, int dir, int ena, int enaval, int emin, int emax, bool limitval, double stepsPerMM, int stepsPerRotation, int acceleration, int maxSpeed){
  STP = stp;                //Step Pin
  DIR = dir;                //Dir Pin
  ENA = ena;                //Enable Pin
  ENAVAL = enaval;          // Enable active Low/High
  EMIN = emin;              // Min Endstop Pin
  EMAX = emax;              // Max Endstop Pin
	LIMITVAL  = limitval;     // Endstop active low/high
  SPM = stepsPerMM;         // Steps per MM (for mm linear motion)
  SPR = stepsPerRotation;   // Steps per Rotation (for RPM and Rotation use cases)
  ACC = acceleration;       // Acceleration arbitrary value
  MAXSPEED = maxSpeed;      // Maximum feedrate in mm/min
  pinMode(EMAX, INPUT);
	pinMode(EMIN, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STP, OUTPUT);
}


void STPDRIVER::enable()
{
	digitalWrite(ENA, ENAVAL);// Activates and deactivates the STPDRIVER chip
	delay (10);               // Delay 10 milliseconds
}

void STPDRIVER::disable()
{
	digitalWrite(ENA, !ENAVAL);// Activates and deactivates the STPDRIVER chip
	delay (10);               // Delay 10 milliseconds
}


void STPDRIVER::motorMoveStep(bool direction) // Move 1 step in Direction
{
	digitalWrite(DIR, direction);
  long pulseDelay = 1/(MAXSPEED/1000000) ;
	digitalWrite(STP, HIGH);
	delayMicroseconds(pulseDelay/2);
	digitalWrite(STP, LOW);
	delayMicroseconds(pulseDelay/2);

}

void STPDRIVER::motorMove(double distance, int speed) // Move distance in mm, in direction
{

  if (speed > MAXSPEED) {
    speed = MAXSPEED;
  }
  if (distance < 0) {
    distance = distance * -1;
    digitalWrite(DIR, LOW);
  } else {
    digitalWrite(DIR, HIGH);
  }

  int slowestPulse = 5000; // Start with a long pulse
  long fastestPulse = 1/(((speed/60)*SPM)/1000000) ;
  int pulseLength = slowestPulse; // Start with a long pulse
  int numOfPulsesToSpeed = (slowestPulse-fastestPulse) / ACC;

  // Run the move
	for(long i = 0; i < distance*SPM; i++){

    // Start Accelerating
    if (i < (distance*SPM)/2) {
      // first half of travel
      if (i < numOfPulsesToSpeed) {
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
          pulseLength = pulseLength - ACC;
      } else {
        // just coasting along...
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
      }
    } else {
      if (i > ((distance*SPM)-numOfPulsesToSpeed)) {
        // Decelerate
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
        pulseLength = pulseLength + ACC;
      } else {
        // just coasting along...
        digitalWrite(STP, HIGH);
        delayMicroseconds(pulseLength/2);
        digitalWrite(STP, LOW);
        delayMicroseconds(pulseLength/2);
      }
    }
	}
}

void STPDRIVER::motorMoveRotations(int rounds, int speed)	// move rotations, in direction
{
  if (rounds < 0) {
    rounds = rounds * -1;
    digitalWrite(DIR, LOW);
  } else {
    digitalWrite(DIR, HIGH);
  }

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
