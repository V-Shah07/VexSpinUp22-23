#include "main.h"
void straight(double, bool);
//void customTurnPID(double target, double maxSpeed, bool left);
void customTurnPID(double target, double maxSpeed, bool left, int minVelocity = 5, double errorThresh = .05);