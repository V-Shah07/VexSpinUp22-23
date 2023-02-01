#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

Motor leftBack(leftBackPort, MOTOR_GEARSET_18, leftBackReversed, MOTOR_ENCODER_DEGREES);
Motor leftFront(leftFrontPort, MOTOR_GEARSET_18, leftFrontReversed, MOTOR_ENCODER_DEGREES);
Motor rightBack(rightBackPort, MOTOR_GEARSET_18,  rightBackReversed, MOTOR_ENCODER_DEGREES);
Motor rightFront(rightFrontPort, MOTOR_GEARSET_18, rightFrontReversed, MOTOR_ENCODER_DEGREES);
Motor leftTop(leftTopPort, MOTOR_GEARSET_18, leftTopReversed, MOTOR_ENCODER_DEGREES);
Motor rightTop(rightTopPort, MOTOR_GEARSET_18, rightTopReversed, MOTOR_ENCODER_DEGREES);

Motor flywheel(flywheelPort, MOTOR_GEARSET_06, flywheelReversed, E_MOTOR_ENCODER_DEGREES);
Motor intake(intakePort, MOTOR_GEARSET_18, intakeReversed, E_MOTOR_ENCODER_DEGREES);
Motor roller(rollerPort, MOTOR_GEARSET_36, rollerReversed, E_MOTOR_ENCODER_DEGREES);
Motor indexer(indexerPort, MOTOR_GEARSET_36, indexerReversed, E_MOTOR_ENCODER_DEGREES);


bool flywheelOn = false;
int intakeMode = 0;
bool intakeOn = false;
int driveReversed = 1;


pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut piston('F');
pros::ADIDigitalOut indexerPiston('E');

pros::IMU inertial(inertialPort);



pros::ADIEncoder trackingEncoder('G', 'H', false);
// pros::ADIEncoder rightEncoder('E', 'F', true);
//pros::ADIEncoder backEncoder('C', 'D', false);

Vision visionSensor(visionSensorPort);
Vision aimbotSensor(visionSensorPort);


// ( vex::PORT1, 50, BLUE ROLLER, RED ROLLER, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7 );