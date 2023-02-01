#include "main.h"
#include "pros/rtos.hpp"


void straight(double inches, bool forward) {
    double Kp = 0.13, Ki = 0.0, Kd = 0.0;
    double error = 0.0, integral = 0.0, derivative = 0.0;
    double previous_error = 0.0;
    trackingEncoder.reset();
    double ticksPerInch = 360 / (4.125 * 3.14159);
    double target = inches * ticksPerInch;

    while(fabs(trackingEncoder.get_value()) <= target)
    {
        
        //controller.print(1, 0, "target: %f", target);
        error = target - fabs(trackingEncoder.get_value());
        if(error < (5*ticksPerInch))
        {
            break;
        }
        integral += error;
        derivative = error - previous_error;

        double power = Kp * error + Ki * integral + Kd * derivative;
        controller.print(0, 0, "Vel: %f", power);
        //controller.print(0, 0, "Encoder: %f", trackingEncoder.get_value());
        // if(power < 3000)
        // {
        //     power = 3000;
        // }
        if(!forward)
        {
            power*=-1;
        }

        leftBack.move_velocity(power);
        rightBack.move_velocity(power);
        leftFront.move_velocity(power);
        rightFront.move_velocity(power);
        leftTop.move_velocity(power);
        rightTop.move_velocity(power);

        previous_error = error;
        pros::delay(10);

    }
    leftBack.move_velocity(0);
    rightBack.move_velocity(0);
    leftFront.move_velocity(0);
    rightFront.move_velocity(0);
    leftTop.move_velocity(0);
    rightTop.move_velocity(0);
}