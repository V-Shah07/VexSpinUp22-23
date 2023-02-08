#include "main.h"
#include <functional>
#include <iostream>
#include <tuple>

#include "EZ-Template/PID.hpp"
#include "EZ-Template/util.hpp"
#include "pros/llemu.hpp"
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

void moveIndexer()
{
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
    {
        indexerPiston.set_value(true);
        pros::delay(100);
        indexerPiston.set_value(false);
    }
    else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {
        for(int i = 0; i < 3; i++)
        {
            indexerPiston.set_value(true);
            pros::delay(250);
            indexerPiston.set_value(false);
            pros::delay(250);
        }
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
    int speed = 5900;
    flywheelPid.set_target(speed);
    int power = flywheelPid.compute(flywheel.get_voltage()) + flywheel.get_voltage();
    flywheel.move_voltage(power);
}