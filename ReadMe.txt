
/* Configure Driver Pinout*/
void pinConfig(int ena, int stp, int dir);

/* Enable Driver (true or false) */
void enable(bool state);

/* Configure Steps per mm (type: Double) */
void stepPerMm(double steps);

/* Configure Steps per Rotation (type: Int) */
void stepPerRotation(int steps);

/* Define Endstops to this Driver
emin: Pin assigned to MIN endstop
emax: Pin assigned to MAX endstop
level = true: endstop triggers HIGH
level = false: endstop triggers LOW */
void endstopConfig(int emin, int emax, bool level);

/* Check that the limit switches are activated before motor movement (true or false) (PIN state DIR) */
bool canGo(bool direction);

/*
	acceleration: The increase (acceleration) or decrease (deceleration) in microseconds between steps (the lower the value, the faster the motor will move)
  maxSpeed: The maximum speed (minimum time in microseconds between the motor steps)
  minSpeed: The minimum speed (maximum time in microseconds between the motor steps) (used as the initial speed of the motor before acceleration, ie the motor starts with the minimum speed and accelerates up to the maximum speed)
	The minimum speed value can not be less than the maximum speed
	The acceleration of the motor is proportional to the minimum speed, the greater the value of the minimum speed the greater the value of the acceleration
*/
void motionConfig(int acceleration, int maxSpeed, int minSpeed);

/* Moves the motor in 1 step, with delay between steps based on the variable SMAX (maximum motor speed, set in the "motionConfig" function)
Usually used in closed loops for continuous motor movement
direction: motor direction (true or false) */
void motorMove(bool direction);

/* Moves the motor a distance in millimeters, with acceleration and deceleration
distance: distance in millimeters
direction: motor direction (true or false) */
void motorMoveTo(double distance, bool direction);

/* Moves the motor an amount of turns, taking into account the number of steps per rotation
rounds: number of whole turns
direction: motor direction (true or false) */
void motorMoveRotations(int rounds, bool direction);

/* Disable the driver's Step pin */
void motorStop();

int ENA;		// En Pin
int DIR;		// Dir Pin
int STP;		// Step Pin
int SPR;		// Steps per Rotation
int EMAX;		// End of Travel
int EMIN;		// Min of Travel
double SPM;		// Steps per millimeter
bool LVL;		// Used to check if the limit switches are activated at high or low level
int ACC;		// Motor acceleration (increase in microseconds at each motor step)
int SMIN;		// Minimum motor speed (time in microseconds between motor steps)
int SMAX;		// Maximum motor speed (time in microseconds between motor steps)
