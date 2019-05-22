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

bool STPDRIVER::canGo(bool direction)
{

	if(LVL) // if: the limit switches activate at a high level
	{

		if(direction && !digitalRead(EMAX)) //if: it moves positively AND the maximum limit switch is not activated
			return true;

		if(!direction && !digitalRead(EMIN)) //if: it moves negatively AND the minimum limit switch is not activated
			return true;

	}
	else if: //the limit switches activate at a low level
	{

		if(direction && digitalRead(EMAX)) //if: it moves positively AND the maximum limit switch is not activated
			return true;

		if(!direction && digitalRead(EMIN)) //if: it moves negatively AND the minimum limit switch is not activated
			return true;

	}
		return false;

}

void STPDRIVER::motionConfig(int acceleration, int maxSpeed, int minSpeed){
	ACC = acceleration;
	SMAX = maxSpeed;

	if(minSpeed < maxSpeed) //Minimum speed value can not be less than the maximum speed value
		SMIN = maxSpeed;
	else
		SMIN = minSpeed;
}



void STPDRIVER::motorMove(bool direction) // Move 1 step in Direction
{
	digitalWrite(DIR, direction);

	if(canGo(direction)){

		digitalWrite(STP, HIGH);
		delayMicroseconds(SMAX/2);
		digitalWrite(STP, LOW);
		delayMicroseconds(SMAX/2);
	}
}

void STPDRIVER::motorMoveTo(double distance, bool direction) // Move distance in mm, in direction
{


	digitalWrite(DIR, direction);
	long accSpeed = SMIN;

	for(long i = 0; i < distance*SPM; i++){

			if(i<(distance*SPM)/2){

				if(accSpeed>SMAX){

					if(canGo(direction)){
						digitalWrite(STP, HIGH);
						delayMicroseconds(accSpeed/2);
						digitalWrite(STP, LOW);
						delayMicroseconds(accSpeed/2);
					}
					else
						delayMicroseconds(accSpeed);
				}
				else
				{
					if(canGo(direction)){
						digitalWrite(STP, HIGH);
						delayMicroseconds(SMAX/2);
						digitalWrite(STP, LOW);
						delayMicroseconds(SMAX/2);
					}
					else
						delayMicroseconds(accSpeed);
				}
				accSpeed = accSpeed - ACC;

			}
			else
			{
				if(accSpeed>SMAX){

					if(canGo(direction)){
						digitalWrite(STP, HIGH);
						delayMicroseconds(accSpeed/2);
						digitalWrite(STP, LOW);
						delayMicroseconds(accSpeed/2);
					}
					else
						delayMicroseconds(accSpeed);
				}
				else
				{
					if(canGo(direction)){
						digitalWrite(STP, HIGH);
						delayMicroseconds(SMAX/2);
						digitalWrite(STP, LOW);
						delayMicroseconds(SMAX/2);
					}
					else
						delayMicroseconds(accSpeed);
				}
				accSpeed = accSpeed + ACC;
			}

	}
}

void STPDRIVER::motorMoveRotations(int rounds, bool direction)	// move rotations, in direction
{
	digitalWrite(DIR, direction);

	for(int r = 0; r < rounds; r++){
		for(int i = 0; i < SPR; i++){

			if(canGo(direction)){

				digitalWrite(STP, HIGH);
				delayMicroseconds(SMAX/2);
				digitalWrite(STP, LOW);
				delayMicroseconds(SMAX/2);
			}
			else
				delayMicroseconds(SMAX);
		}
	}

}

void STPDRIVER::motorStop() //Disable Step
{
	digitalWrite(STP, LOW);
}
