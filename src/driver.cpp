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
    pros::lcd::print(1, "leftback: %f", flywheel.get_temperature());
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
    {
        flywheelOn = !flywheelOn;
    }
    if (flywheelOn)
    {
        flywheel = 82;
        pros::lcd::print(1, "flywheel: %f", flywheel.get_actual_velocity());
    }
    else
        flywheel.move_velocity(0);
}

void moveIndexer()
{
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
    {
        indexerPiston.set_value(true);
        pros::delay(500);
        indexerPiston.set_value(false);
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
