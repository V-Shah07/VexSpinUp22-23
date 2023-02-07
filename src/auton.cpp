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

double realHeading(double heading)
{
    if(heading <= 180)
    {
        return heading;
    }

    return -1 * (360-heading);

}

void customTurnPID(double target, double maxSpeed, bool left)
{
    double Kp = 0.5, Ki = 0.0, Kd = 0.0;
    bool pidEnabled = true;
    
    int velCap = 0;
    int accel = 5;
    
    double error, integral = 0, derivative = 0;
    double previous_error = 0;
    double power = 0;

    double errorThresh = 0.05, derivativeThresh = 0.00001;
    int sign = 1;
    if(!left)
    {
        sign = -1;
    }

    leftFront.tare_position();
    leftBack.tare_position();
    leftTop.tare_position();
    rightFront.tare_position();
    rightBack.tare_position();
    rightTop.tare_position();

    int refreshRate = 10;
    int timeSettled = 50;
    int minVelocity = 5;
    int iterationSetlled = timeSettled/refreshRate;
    target = realHeading(target);
    while(pidEnabled)
    {
        double curAngle = realHeading(inertial.get_heading());
        error = target - curAngle;

        integral += error;
        derivative = error - previous_error;
        power = Kp * error + Ki * integral + Kd * derivative;

        if((fabs(error) < errorThresh) && (fabs(power) < 1) /*&& (fabs(derivative) < derivativeThresh)*/)
        {
            // iterationSetlled--;
            // if(iterationSetlled <= 0)
            // {
            //     pidEnabled = false;
            // }
            pidEnabled = false;
        }
        else
        {
            iterationSetlled = timeSettled/refreshRate;
        }

        if(fabs(power) < minVelocity)
        {
            power = minVelocity * (power/fabs(power));
        }
        /*
        //Capping the velocity
        velCap += accel;
        if(velCap > maxSpeed)
        {
            velCap = maxSpeed;
        }
        if(fabs(power) > velCap)
        {
            power = velCap * (power/fabs(power));
        }
        
        //adjusting for drift
        int rDiff = fabs((leftFront.get_position() + leftTop.get_position() + leftBack.get_position())/3) - fabs((rightFront.get_position() + rightTop.get_position() + rightBack.get_position())/3);
        double rMod = rDiff * 0.1 * sign;
        */
        
        int leftPower = power;
        int rightPower = sign * power /*+ rMod*/;
        controller.print(0, 0, "power: %d", power);
        pros::lcd::set_text(2, "power: " + std::to_string(power));
        pros::lcd::set_text(3, "error: " + std::to_string(error));

        leftBack.move_velocity(leftPower);
        rightBack.move_velocity(rightPower);
        leftFront.move_velocity(leftPower);
        rightFront.move_velocity(rightPower);
        leftTop.move_velocity(leftPower);
        rightTop.move_velocity(rightPower);

        lastError = error;

        pros::delay(refreshRate);
    }
    leftBack.move_velocity(0);
    rightBack.move_velocity(0);
    leftFront.move_velocity(0);
    rightFront.move_velocity(0);
    leftTop.move_velocity(0);
    rightTop.move_velocity(0);

}