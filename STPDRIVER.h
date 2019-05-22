#ifndef STPDRIVER_H
#define STPDRIVER_H

#include <Arduino.h>

class STPDRIVER{
public:
	STPDRIVER(int ena, int stp, int dir);

	void enable(bool state);
	void stepPerMm(double steps);
	void stepPerRotation(int steps);
	void stepConfig(int s);
	void endstopConfig(int emin, int emax, bool level);
	bool canGo(bool direction);
	void motionConfig(int acceleration, int maxSpeed);
	void motorMoveStep(bool direction);
	void motorMove(double distance);
	void motorMoveRotations(int rounds, bool direction, int speed);


// Global Variables
	int ENA;              // Enable Pin
	int DIR;              // Dir Pin
	int STP;              // Step Pin
	int SPR;	      // Steps per Rotation
	int EMAX;	      // MAX Endstop Pin
	int EMIN;	      // MIN Endstop Pin
	double SPM;           // Steps per MM
	bool LVL;	      // Limit Switch mode (LOW or HIGH)
	int ACC;		//Motor acceleration (increase in microseconds at each motor step)
	int MAXSPEED;

};

#endif
