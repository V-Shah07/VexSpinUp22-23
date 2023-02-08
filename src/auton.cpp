#include "main.h"
#include "pros/rtos.hpp"


void straight(double inches, bool forward) {
    double Kp = 0.5, Ki = 0.0, Kd = 0.0;
    double error = 0.0, integral = 0.0, derivative = 0.0;
    double previous_error = 0.0;
    leftFront.tare_position();
    trackingEncoder.reset();
    double ticksPerInch = 360 / (4.125 * 3.14159);
    double target = inches * ticksPerInch;
    double minPower = 600;

    controller.clear();
    while(fabs(leftFront.get_position()) <= target)
    {
        
        //controller.print(1, 0, "target: %f", target);
        error = target - fabs(leftFront.get_position());
        if(error < (5*ticksPerInch))
        {
            break;
        }
        integral += error;
        derivative = error - previous_error;

        double power = Kp * error + Ki * integral + Kd * derivative;
        if (power < 5) break;
        //controller.print(0, 0, "error: %i", round(error));
        //controller.print(0, 0, "Encoder: %f", trackingEncoder.get_value());
        // if(power < 3000)
        // {
        //     power = 3000;
        // }
        if(!forward)
        {
            power*=-1;
        }
        //if (power < minPower) minPower = power;
        
        //controller.print(1, 1, "Target: %f", target);
        controller.print(0, 0, "Current: %f", leftFront.get_position());

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

void customTurnPID(double target, double maxSpeed, bool left, int minVelocity, double errorThresh)
{
    double Kp = 0.5, Ki = 0.0, Kd = 0.0;
    bool pidEnabled = true;
    
    int velCap = 0;
    int accel = 5;
    
    double error, integral = 0, derivative = 0;
    double previous_error = 0;
    double power = 0;

    double derivativeThresh = 0.05;
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
    //int minVelocity = 5;
    int iterationSetlled = timeSettled/refreshRate;


    while(pidEnabled)
    {
        double curAngle = inertial.get_heading();
        error = target - curAngle;

        //3 possible angles
        int two, three;
        int one = error;
        two = error + 360;
        three = error - 360;
        
        if(fabs(one) < fabs(two) && fabs(one) < fabs(three))
        {
            error = one;
        }
        else if(fabs(two) < fabs(one) && fabs(two) < fabs(three))
        {
            error = two;
        }
        else
        {
            error = three;
        }

        //if (!left) error *= -1;

        integral += error;
        derivative = error - previous_error;
        power = Kp * error + Ki * integral + Kd * derivative;

        if((fabs(error) < errorThresh) && (fabs(power) < 1)/* && (fabs(derivative) < derivativeThresh)*/)
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
        }*/
        
        //adjusting for drift
        // int rDiff = fabs((leftFront.get_position() + leftTop.get_position() + leftBack.get_position())/3) - fabs((rightFront.get_position() + rightTop.get_position() + rightBack.get_position())/3);
        // double rMod = rDiff * 0.1 * sign;
        double rMod = 0;
        
        int leftPower, rightPower;
        int curPowerSign = power/fabs(power);
        if(left)
        {
            //this means leftpower has to be negative

            if(curPowerSign == 1)
            {
                leftPower = -1 * power;
                rightPower = power;
            }
            else
            {
                leftPower = power;
                rightPower = -1 * power;
            }
        }
        else
        {
            //this means rightpower has to be negative
            if(curPowerSign == 1)
            {
                leftPower = power;
                rightPower = -1 * power;
            }
            else
            {
                leftPower = -1 * power;
                rightPower = power;
            }
        }
        //controller.print(0, 0, "Angle: %i", round(inertial.get_heading()));
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