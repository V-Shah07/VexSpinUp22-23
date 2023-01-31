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


const bool flywheelReversed = true;
const bool intakeReversed = false;
const bool rollerReversed = true;
const bool indexerReversed = false;



extern Motor leftBack;
extern Motor rightBack;
extern Motor leftFront;
extern Motor rightFront;
extern Motor leftTop;
extern Motor rightTop;


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

//extern vision_signature_s_t BLUE_ROLLER;
//extern vision_signature_s_t RED_ROLLER;

const int blue_sig = 1;
const int red_sig = 2;

const bool RED = true;
const bool BLUE = false;

const bool color = BLUE;


extern pros::IMU inertial;

const double targetAngle = 45.0;
