#include "main.h"
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

#include "EZ-Template/PID.hpp"
#include "EZ-Template/util.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

void moveFlywheel()
{
    int target = 8030;
    int error = target - flywheel.get_voltage();
    integral += error;
    int derviative = error - lastError;

    double power = (error * flywheelKp) + (integral * flywheelKi) + (derviative * flywheelKd);

    flywheel.move_voltage(power);

    lastError = error;
}

void moveIndexer() // shooting
{
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) // Single shot
    {
        indexerPiston.set_value(true);
        pros::delay(100);
        indexerPiston.set_value(false);
    }
    else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) // Rapid fire three shots
    {
        Task rapidFireTask(rapidFire); // Start the task that runs three shots without blocking the main thread
    }
}

// Method for the task that shoots 3 discs
void rapidFire()
{
    for(int i = 0; i < 3; i++) // Fire 3 shots
    {
        indexerPiston.set_value(true);
        pros::delay(100);
        indexerPiston.set_value(false);
        if (i == 2) break;
        else if (i == 1) pros::delay(400);
        else pros::delay(300);
    }
}

void moveIntake()
{
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
    {
        if (intakeMode == 1)
            intakeMode = 0;
        else
            intakeMode = 1;
    }
    else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2))
    {
        if (intakeMode == 2)
            intakeMode = 0;
        else
            intakeMode = 2;
    }

    if (intakeMode == 1)
    {
        intake = 200 ;
    }
    else if (intakeMode == 2)
    {
        intake = -200;
    }
    else
    {
        intake.move_velocity(0);
    }
}

void expand()
{
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B))
    {
        piston.set_value(true);
    }
}

void flywheelMaintainer()
{
    int velocityTarget = 480;
    bool flywheel_on = true;
    controller.clear();
    grapher->addDataType("Desired Vel", COLOR_ORANGE);
    grapher->addDataType("Actual Vel", COLOR_AQUAMARINE);

    grapher->startTask();
    while (true) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            velocityTarget += 10;
            controller.print(0,  0, "Target: %f", velocityTarget);
            pros::lcd::set_text(2, "target: " + std::to_string(velocityTarget));
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            velocityTarget -= 10;
            controller.print(0, 0, "Target: %f", velocityTarget);
            pros::lcd::set_text(2, "target: " + std::to_string(velocityTarget));
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            flywheel_on = !flywheel_on;
        }
        flywheelPid.set_target(velocityTarget);
        int velocity = flywheelPid.compute(flywheel.get_actual_velocity()) + velocityTarget;
        if (velocity < velocityTarget) velocity = velocityTarget;
        if (flywheel_on) flywheel.move_voltage(velocity * 20);
        else flywheel.move_voltage(0);
        pros::lcd::set_text(1, "Current: " + std::to_string(flywheel.get_actual_velocity()));

        grapher->update("Desired Vel", velocityTarget);
        grapher->update("Actual Vel", flywheel.get_actual_velocity());
        pros::delay(10);
        
    }

}