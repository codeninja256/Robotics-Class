#pragma config(UserModel, "base_code.h")
#include "base_code.h"

task main()
{
	//ALWAYS START CHALLENGE WITH CLAW CLOSED!!!
	forward((2 * 12 - 0.5) / WHEEL_CIRCUM);
	doNothing(1000);
	turnLeft(0.8);
	doNothing(1000);
	forward((2.4 * 12 + 1) / WHEEL_CIRCUM);
	doNothing(1000);
	turnLeft(0.75);
	doNothing(1000);
	openClaw();
	doNothing(1000);
	forward(13.25 / WHEEL_CIRCUM);
	doNothing(1000);
	closeClaw();
	doNothing(1000);
	moveArmUp(900);
	doNothing(1000);
	turnLeft(1.5);
	doNothing(1000);
	forward((2.7 * 12 + 3) / WHEEL_CIRCUM);
	doNothing(1000);
	turnRight(0.7);
	doNothing(1000);
	moveArmUp(200);
	doNothing(1000);
	forward(2.5 / WHEEL_CIRCUM);
	doNothing(1000);
	openClaw();
	doNothing(1000);
	moveArmUp(300);
	doNothing(1000);
	backward(2 / WHEEL_CIRCUM);
	doNothing(1000);
	moveArmDown(600);
	doNothing(1000);
	forward(2.5 / WHEEL_CIRCUM);
	doNothing(1000);
	closeClaw();
	doNothing(1000);
	moveArmUp(900);
	doNothing(1000);
	turnRight(0.7);
	doNothing(1000);
	forward(1.5 * 12 / WHEEL_CIRCUM);
	doNothing(1000);
	turnLeft(0.7);
	doNothing(1000);
	forward(2 * 12 / WHEEL_CIRCUM);
	doNothing(1000);
	turnLeft(0.7);
	doNothing(1000);
	forward(12 / WHEEL_CIRCUM);
	doNothing(1000);
	moveArmDown(900);
	doNothing(1000);
	openClaw();
}
