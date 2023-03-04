#include "autons.hpp"
#include "ARMS/chassis.h"
#include "ARMS/flags.h"
#include "EZ-Template/drive/drive.hpp"
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
  ez_chassis.set_slew_min_power(80, 80);
  ez_chassis.set_slew_distance(7, 7);
  ez_chassis.set_pid_constants(&ez_chassis.headingPID, .1, 0, 20, 0);
  ez_chassis.set_pid_constants(&ez_chassis.forward_drivePID, 0.45, 0, 5, 0);
  ez_chassis.set_pid_constants(&ez_chassis.backward_drivePID, 0.45, 0, 5, 0);
  ez_chassis.set_pid_constants(&ez_chassis.turnPID, 7.0, 0.003, 35, 15);
  ez_chassis.set_pid_constants(&ez_chassis.swingPID, 7, 0, 45, 0);
}


void exit_condition_defaults() {
  ez_chassis.set_exit_condition(ez_chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  ez_chassis.set_exit_condition(ez_chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  ez_chassis.set_exit_condition(ez_chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  ez_chassis.set_exit_condition(ez_chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  ez_chassis.set_exit_condition(ez_chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  ez_chassis.set_exit_condition(ez_chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  double exit_error = .1;
  arms::chassis::move(24);
  arms::chassis::waitUntilFinished(exit_error);
  arms::chassis::move(12, arms::REVERSE);
  arms::chassis::waitUntilFinished(exit_error);
  arms::chassis::move(-12, arms::REVERSE);
  arms::chassis::waitUntilFinished(exit_error);
  flywheel.move_velocity(600);
  // //dummy
  // ez_chassis.wait_drive();
  // ez_chassis.set_drive_pid(0.2, DRIVE_SPEED);
  // ez_chassis.wait_drive();
  // ez_chassis.set_drive_pid(-1, DRIVE_SPEED);
  // ez_chassis.wait_drive();
  // pros::delay(1000);
  // ez_chassis.set_drive_pid(-1, DRIVE_SPEED);
  // ez_chassis.wait_drive();
  // pros::delay(1000);
  //   ez_chassis.set_drive_pid(2, DRIVE_SPEED, true);
  // ez_chassis.wait_drive();
  // pros::delay(1000);
  // ez_chassis.set_turn_pid(90, TURN_SPEED);
  // ez_chassis.wait_drive();
  // pros::delay(1000);
  // ez_chassis.set_turn_pid(-90, TURN_SPEED);
  // ez_chassis.wait_drive();
  // pros::delay(1000);
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  ez_chassis.set_turn_pid(90, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(0, TURN_SPEED);
  ez_chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(-45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(0, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  ez_chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
  ez_chassis.wait_until(6);
  ez_chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(-45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(0, TURN_SPEED);
  ez_chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  ez_chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  ez_chassis.wait_until(-6);
  ez_chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  ez_chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  ez_chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
  ez_chassis.wait_until(12);

  ez_chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  ez_chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(0, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  ez_chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    ez_chassis.set_drive_pid(-12, 127);
    ez_chassis.wait_drive();

    // If failsafed...
    if (ez_chassis.interfered) {
      ez_chassis.reset_drive_sensor();
      ez_chassis.set_drive_pid(-2, 20);
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
 ez_chassis.set_drive_pid(24, DRIVE_SPEED, true);
 ez_chassis.wait_drive();

 if (ez_chassis.interfered) {
   tug(3);
   return;
 }

 ez_chassis.set_turn_pid(90, TURN_SPEED);
 ez_chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .
void Test()
{
//flywheel.move_voltage(12000);
  //ez_chassis.wait_drive();
  ez_chassis.set_drive_pid(-tileLength*0.25, 80);
  ez_chassis.wait_drive();
  intake.move_velocity(100);
  pros::delay(2000);
  pros::delay(300);
  intake.move_velocity(0);
}

void front_auton()
{
  flywheel.move_voltage(9000);
  //ez_chassis.wait_drive();


  //roller
  ez_chassis.set_drive_pid(-tileLength*0.3, DRIVE_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(100);
  pros::delay(150);
  intake.move_velocity(0);

  //move off roller 
  ez_chassis.set_drive_pid(tileLength * .3, DRIVE_SPEED);
  ez_chassis.wait_drive();

  //turn to lowgoal
  ez_chassis.set_turn_pid(90, TURN_SPEED);
  ez_chassis.wait_drive();

  // controller.print(0, 0, "Flywheel: %f", flywheel.get_actual_velocity());

  //shoot
  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(120);
    flywheel.move_voltage(9000);
    indexerPiston.set_value(false);
    pros::delay(200);
  }
  pros::delay(200);
  flywheel.move_voltage(12000);

  //turn to 3 stack
  ez_chassis.set_turn_pid(-130, TURN_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(-200);

  //intake 3 stack 
  ez_chassis.set_drive_pid(-tileLength *2.3 , DRIVE_SPEED/1.5);
  ez_chassis.wait_drive();
  pros::delay(500);

  //turn to goal 
  ez_chassis.set_turn_pid(-45, TURN_SPEED);
  ez_chassis.wait_drive();
  
  flywheel.move_velocity(550);
  // ez_chassis.set_drive_pid(-tileLength * .2, DRIVE_SPEED / 2);
  // ez_chassis.wait_drive();
  ez_chassis.set_turn_pid(-34, TURN_SPEED);
  ez_chassis.wait_drive();
  pros::delay(3000);
  //shoot 
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    flywheel.move_velocity(600);
    indexerPiston.set_value(false);
    ez_chassis.set_turn_pid(-36.0, TURN_SPEED);
    ez_chassis.wait_drive();
    pros::delay(600);
   
  }
  // pros::delay(100);
  // intake.move_velocity(0);
  // for(int i = 0; i < 3; i++)
  // {
  //   indexerPiston.set_value(true);
  //   pros::delay(300);
  //   indexerPiston.set_value(false);
  //   pros::delay(300);
  // }
}

void front_auton_arms()
{
  double exit_error = .1;
  flywheel.move_voltage(9000);
  //ez_chassis.wait_drive();


  //roller
  arms::chassis::move(-24 * .3);
  arms::chassis::waitUntilFinished(exit_error);
  intake.move_velocity(100);
  pros::delay(150);
  intake.move_velocity(0);

  //move off roller 
  arms::chassis::move(24 * .3);
  arms::chassis::waitUntilFinished(exit_error);

  //turn to lowgoal
  arms::chassis::turn(90);
  arms::chassis::waitUntilFinished(exit_error);

  // controller.print(0, 0, "Flywheel: %f", flywheel.get_actual_velocity());

  //shoot
  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(120);
    flywheel.move_voltage(9000);
    indexerPiston.set_value(false);
    pros::delay(200);
  }
  pros::delay(200);
  flywheel.move_voltage(12000);

  //turn to 3 stack
  arms::chassis::turn(-130);
  arms::chassis::waitUntilFinished(exit_error);
  intake.move_velocity(-200);

  //intake 3 stack 
  arms::chassis::move(24 * -2.3);
  arms::chassis::waitUntilFinished(exit_error);
  // ez_chassis.set_drive_pid(-tileLength *2.3 , DRIVE_SPEED/1.5);
  // ez_chassis.wait_drive();
  pros::delay(500);

  //turn to goal 
  ez_chassis.set_turn_pid(-45, TURN_SPEED);
  ez_chassis.wait_drive();
  
  flywheel.move_velocity(550);
  // ez_chassis.set_drive_pid(-tileLength * .2, DRIVE_SPEED / 2);
  // ez_chassis.wait_drive();
  ez_chassis.set_turn_pid(-34, TURN_SPEED);
  ez_chassis.wait_drive();
  pros::delay(3000);
  //shoot 
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    flywheel.move_velocity(600);
    indexerPiston.set_value(false);
    ez_chassis.set_turn_pid(-36.0, TURN_SPEED);
    ez_chassis.wait_drive();
    pros::delay(600);
   
  }
  // pros::delay(100);
  // intake.move_velocity(0);
  // for(int i = 0; i < 3; i++)
  // {
  //   indexerPiston.set_value(true);
  //   pros::delay(300);
  //   indexerPiston.set_value(false);
  //   pros::delay(300);
  // }
}

void easy_prog_skills()
{
  flywheel.move_velocity(500);
  ez_chassis.set_drive_pid(-tileLength*0.4, DRIVE_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(-100);
  pros::delay(600);
  intake.move_velocity(0);

  ez_chassis.set_drive_pid(tileLength * 0.7, DRIVE_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(-100);
  ez_chassis.set_turn_pid(90.0, TURN_SPEED);
  ez_chassis.wait_drive();
  ez_chassis.set_drive_pid(-tileLength * 1.1, DRIVE_SPEED);
  ez_chassis.wait_drive();
  pros::delay(600);
  intake.move_velocity(0);
  ez_chassis.set_drive_pid(tileLength * 1, DRIVE_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(-100);
  pros::delay(5000);
  intake.move_velocity(0);
  ez_chassis.set_turn_pid(110.0, TURN_SPEED);
  ez_chassis.wait_drive();
  for(int i = 0; i < 3; i++)
  {
    //flywheel.move_voltage(12000);
    indexerPiston.set_value(true);
    pros::delay(100);
    indexerPiston.set_value(false);
    //flywheel.move_voltage(12000);
    pros::delay(2000);
  }
  ez_chassis.set_turn_pid(-135.0, TURN_SPEED);
  ez_chassis.wait_drive();
  ez_chassis.set_drive_pid(tileLength * .6, DRIVE_SPEED);
  ez_chassis.wait_drive();
  piston.set_value(true);
}

void new_left_auton()
{
  flywheel.move_voltage(9000);
  pros::delay(1000); 
  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(100);
    indexerPiston.set_value(false);
    pros::delay(200);
  }
  flywheel.move_voltage(12000);
  
  ez_chassis.set_turn_pid(-137, TURN_SPEED);
  ez_chassis.wait_drive();
  intake.move_velocity(-100);
  ez_chassis.set_drive_pid(-tileLength * 2.2, DRIVE_SPEED / 2);
  ez_chassis.wait_drive();
  ez_chassis.set_turn_pid(143, TURN_SPEED);
  
  ez_chassis.wait_drive();
  ez_chassis.set_drive_pid(tileLength * .2, DRIVE_SPEED);
  ez_chassis.wait_drive();
  flywheel.move_voltage(12000);
  for(int i = 0; i < 2; i++)
  {
    //flywheel.move_voltage(12000);
    indexerPiston.set_value(true);
    pros::delay(100);
    indexerPiston.set_value(false);
    flywheel.move_voltage(12000);
    pros::delay(2000);
  }
}


void right_auton()
{
  flywheel.move_voltage(12000);
  ez_chassis.set_drive_pid(-tileLength*0.4, DRIVE_SPEED);
  ez_chassis.wait_drive();
  ez_chassis.set_turn_pid(90, TURN_SPEED);
  ez_chassis.wait_drive();
  ez_chassis.set_drive_pid(-tileLength*0.9, DRIVE_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(170, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-tileLength*0.35, DRIVE_SPEED);
  ez_chassis.wait_drive();

  intake.move_velocity(100);
  pros::delay(300);
  intake.move_velocity(0);

  ez_chassis.set_drive_pid(tileLength*0.25, DRIVE_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(90, TURN_SPEED);
  ez_chassis.wait_drive();

  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    indexerPiston.set_value(false);
    pros::delay(400);
  }
  intake.move_velocity(-200);
  ez_chassis.set_turn_pid(-50, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-tileLength*2.5, DRIVE_SPEED*0.5);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(45, TURN_SPEED);
  ez_chassis.wait_drive();
  flywheel.move_voltage(6000);
  pros::delay(1000);
  for(int i = 0; i < 3; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    indexerPiston.set_value(false);
    pros::delay(400);
  }
}
void prog_skills()
{
  ez_chassis.set_turn_pid(10.0, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-tileLength, DRIVE_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(-100.0, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-tileLength * 0.6, DRIVE_SPEED);
  ez_chassis.wait_drive();

  intake.move_velocity(200);
  pros::delay(300);

  ez_chassis.set_drive_pid(tileLength * 0.6, DRIVE_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(90.0, TURN_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_drive_pid(-tileLength , DRIVE_SPEED);
  ez_chassis.wait_drive();

  intake.move_velocity(-200);
  pros::delay(500);

  ez_chassis.set_drive_pid(tileLength * 0.6, DRIVE_SPEED);
  ez_chassis.wait_drive();

  ez_chassis.set_turn_pid(-45.0, TURN_SPEED);
  ez_chassis.wait_drive();

  //piston.set_value(true);
}

void final_auton()
{
  ez_chassis.set_drive_pid(-0.4 * tileLength, DRIVE_SPEED);
  ez_chassis.wait_drive();
  
  intake.move_velocity(200);
  pros::delay(300);

  ez_chassis.set_drive_pid(0.6 * tileLength, DRIVE_SPEED);
  ez_chassis.wait_drive();

  for(int i = 0; i < 2; i++)
  {
    indexerPiston.set_value(true);
    pros::delay(400);
    indexerPiston.set_value(false);
    pros::delay(400);
  }

  ez_chassis.set_turn_pid(-45.0, TURN_SPEED);
  ez_chassis.wait_drive();

  }