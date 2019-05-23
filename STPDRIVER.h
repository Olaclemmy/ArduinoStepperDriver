#ifndef STPDRIVER_H
#define STPDRIVER_H

#include <Arduino.h>

class STPDRIVER{
public:
	STPDRIVER(int stp, int dir, int ena, int enaval, int emin, int emax, bool limitval, double stepsPerMM, int stepsPerRotation, int acceleration, int maxSpeed);
	void enable();
	void disable();
	void motorMoveStep(bool direction);
	void motorMove(double distance, int speed);
	void motorMoveRotations(int rounds,  int speed);
	// Global Variables
	int STP;       // Step Pin
	int DIR;       // Dir Pin
	int ENA;       // Enable Pin
	int ENAVAL;		 // // Enable active Low/High
	int EMIN;	     // MIN Endstop Pin
	int EMAX;	     // MAX Endstop Pin
	int LIMITVAL;	 // Endstop active low/high
	double SPM;    // Steps per MM
	int SPR;	     // Steps per Rotation
	int ACC;			 // Motor acceleration (larger = faster)
	int MAXSPEED;  // Max feed in mm/min
};

#endif
