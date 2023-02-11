#include "main.h"

const int leftFrontPort = 3;
const int rightFrontPort = 1;
const int leftBackPort = 6;
const int rightBackPort = 4;
const int leftTopPort = 5;
const int rightTopPort = 2;


const int flywheelPort = 11;
const int intakePort = 8;
const int rollerPort = 8;
const int indexerPort = 10;

const int inertialPort = 12;

const int visionSensorPort = 9;
const int aimbotSensorPort = 18;

const bool leftBackReversed = true;
const bool rightBackReversed = false;
const bool leftFrontReversed = true;
const bool rightFrontReversed = false;
const bool leftTopReversed = false;
const bool rightTopReversed = true;


const bool flywheelReversed = false;
const bool intakeReversed = false;
const bool rollerReversed = true;
const bool indexerReversed = false;



extern Motor leftBack;
extern Motor rightBack;
extern Motor leftFront;
extern Motor rightFront;
extern Motor leftTop;
extern Motor rightTop;

extern PID flywheelPid;

extern Motor flywheel;
extern Motor intake;
extern Motor roller;
extern Motor indexer;

extern bool flywheelOn;
extern bool intakeOn;
extern int intakeMode;
extern int driveReversed;


extern pros::Controller controller;

extern pros::ADIDigitalOut piston;
extern pros::ADIDigitalOut indexerPiston;

extern pros::ADIEncoder trackingEncoder;

extern pros::Vision visionSensor;
extern pros::Vision aimbotSensor;

extern Task maintainFlywheel;
extern Task rapidFireTask;

//extern vision_signature_s_t BLUE_ROLLER;
//extern vision_signature_s_t RED_ROLLER;

const int blue_sig = 1;
const int red_sig = 2;

const bool RED = true;
const bool BLUE = false;

const bool color = BLUE;


const double flywheelKp = 0.4, flywheelKi = 0.0, flywheelKd = 0.0;
extern double integral, lastError;

extern pros::IMU inertial;

const double targetAngle = 45.0;

const int tileLength = 2;

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
