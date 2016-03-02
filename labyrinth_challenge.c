#pragma config(UserModel, "base_code.h")
#include "base_code.h"

task main()
{
	forward(2*12/WHEEL_CIRCUM);
	doNothing(1000);
	turnLeft(0.8);
	doNothing(1000);
	forward(2.5*12/WHEEL_CIRCUM);
	doNothing(1000);
	turnRight(0.9);
	doNothing(1000);
	forward(1.5*12/WHEEL_CIRCUM);
	doNothing(1000);
	turnRight(0.8);
	doNothing(1000);
	openClaw();
	doNothing(1000);
	forward(12/WHEEL_CIRCUM);
	doNothing(1000);
	closeClaw();
	doNothing(1000);
	moveArmUp(900);
	doNothing(1000);
	turnLeft(1.6);
	forward(12/WHEEL_CIRCUM);
	turnLeft(0.8);
	forward(1.5*12/WHEEL_CIRCUM);
	turnLeft(0.8);
	forward(2.5*12/WHEEL_CIRCUM);
	turnLeft(0.8);
	forward(2*12/WHEEL_CIRCUM);
	moveArmDown(900);
	openClaw();
	backward(4*12/WHEEL_CIRCUM);
}
