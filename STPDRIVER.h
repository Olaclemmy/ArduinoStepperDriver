#ifndef STPDRIVER_H
#define STPDRIVER_H

#include <Arduino.h>

class STPDRIVER{
public:
	STPDRIVER();

	void pinConfig(int ena, int stp, int dir);
	void enable(bool state);
	void stepPerMm(double steps);
	void stepPerRound(int steps);
	void stepConfig(int s);
	void endstopConfig(int emin, int emax, bool level);
	bool canGo(bool direction);
	void motionConfig(int acceleration, int maxSpeed, int minSpeed);
	void motorMove(bool direction);
	void motorMoveTo(double distance, bool direction);
	void motorMoveRotations(int rounds, bool direction);
	void motorStop();

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
	int SMIN;		// Minimum motor speed (time in microseconds between motor steps)
	int SMAX;		// Maximum motor speed (time in microseconds between motor steps) 
};

#endif
