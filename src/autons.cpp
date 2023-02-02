#include "autons.hpp"
#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////






///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, .1, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  chassis.set_drive_pid(2, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-1, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-1, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .
void Test()
{
//chassis.set_drive_pid(2, DRIVE_SPEED, true);
chassis.set_pid_constants(&chassis.forward_drivePID, 0.1, 0, 0, 0);

//chassis.set_drive_pid(24, DRIVE_SPEED, false, true);

chassis.set_pid_constants(&chassis.turnPID, 3, 0.003, 35, 15);
chassis.set_turn_pid(-90, 100);
chassis.wait_drive();
chassis.reset_pid_targets();
chassis.set_turn_pid(0, 100);
}

void main_auton()
{
  flywheel.move_voltage(12000);
  chassis.set_drive_pid(-0.7, 80);
  intake.move_velocity(100);
  pros::delay(250);
  intake.move_velocity(0);

  chassis.set_drive_pid(0.5, 80);
  chassis.set_turn_pid(-80, TURN_SPEED);
  chassis.wait_drive();

  controller.print(0, 0, "Flywheel: %f", flywheel.get_actual_velocity());

  pros::delay(1000);
  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    indexerPiston.set_value(false);
    pros::delay(400);
  }
  pros::delay(200);

  chassis.set_turn_pid(125, -TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(-100);
  
  chassis.set_drive_pid(-tileLength* 2.5, DRIVE_SPEED/2);
  chassis.wait_drive();
  
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  pros::delay(100);
  intake.move_velocity(0);
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(300);
    indexerPiston.set_value(false);
    pros::delay(300);
  }
}

void prog_skills()
{
  flywheel.move_voltage(12000);
  chassis.set_drive_pid(-0.7, 80);
  intake.move_velocity(100);
  pros::delay(250);
  intake.move_velocity(0);

  chassis.set_drive_pid(0.5, 80);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(tileLength * 2, DRIVE_SPEED);
  

  pros::delay(1000);
  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    indexerPiston.set_value(false);
    pros::delay(400);
  }
  pros::delay(200);

  chassis.set_drive_pid(-tileLength * 2, DRIVE_SPEED);

  chassis.set_turn_pid(135, -TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(-100);
  
  chassis.set_drive_pid(-tileLength* 2.5, DRIVE_SPEED/2);
  chassis.wait_drive();
  
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(0);
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(300);
    indexerPiston.set_value(false);
    pros::delay(300);
  }
  pros::delay(200);

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(-100);

  chassis.set_drive_pid(-tileLength* 3, DRIVE_SPEED/2);
  chassis.wait_drive();
  
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(0);
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(300);
    indexerPiston.set_value(false);
    pros::delay(300);
  }
  pros::delay(200);

  chassis.set_turn_pid(60, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-tileLength * 2, DRIVE_SPEED / 2);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-0.7, 80);
  intake.move_velocity(100);
  pros::delay(250);
  intake.move_velocity(0);

  chassis.set_drive_pid(0.5, 80);
}