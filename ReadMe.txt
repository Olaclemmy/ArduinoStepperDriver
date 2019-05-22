

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

/* Acceleration:  Between >1 and <maxSpeed. maxSpeed is maximum feedrate */
void motionConfig(int acceleration, int maxSpeed, );

/* Moves the motor in 1 step, with delay between steps based on the variable SMAX (maximum motor speed, set in the "motionConfig" function)
Usually used in closed loops for continuous motor movement
direction: motor direction (true or false) */
void motorMoveStep(bool direction);

/* Moves the motor a distance in millimeters, with acceleration and deceleration
distance: distance in millimeters (negative to reverse)
void motorMove(double distance);

/* Moves the motor an amount of turns, taking into account the number of steps per rotation
rounds: number of whole turns
direction: motor direction (true or false) */
speed: mm/min
void motorMoveRotations(int rounds, bool direction, int speed);

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
