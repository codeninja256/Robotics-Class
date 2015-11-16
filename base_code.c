#pragma config(StandardModel, "RVW CLAWBOT")

const float NORMAL_SPEED=63;
const float SLOW_SPEED=40;
const float ROTATIONS_TO_TICKS=627.2;
const int AXLE_LENGTH=11;
const int WHEEL_DIAMETER=4;

void resetEncoders();
void doNothing(int ms);
void forward(float rotations);
void turnLeft(float rotations);
void turnRight(float rotations);

void resetEncoders()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
}

void doNothing(int ms)
{
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	wait1Msec(ms);
}

void forward(float rotations)
{
	resetEncoders();
	while(abs(getMotorEncoder(rightMotor))<rotations*ROTATIONS_TO_TICKS && abs(getMotorEncoder(leftMotor))<rotations*ROTATIONS_TO_TICKS)
	{
		if(abs(getMotorEncoder(rightMotor))<abs(getMotorEncoder(leftMotor))) //if leftMotor has gone farther...
		{
			motor[rightMotor]=NORMAL_SPEED;
			motor[leftMotor]=SLOW_SPEED; //slow down leftMotor
		}
		if(abs(getMotorEncoder(rightMotor))>abs(getMotorEncoder(leftMotor))) //if rightMotor has gone farther...
		{
			motor[rightMotor]=SLOW_SPEED; //slow down rightMotor
			motor[leftMotor]=NORMAL_SPEED;
		}
		if(abs(getMotorEncoder(rightMotor))==abs(getMotorEncoder(rightMotor))) //if rightMotor and leftMotor have gone the same distance
		{
			motor[rightMotor]=NORMAL_SPEED;
			motor[leftMotor]=NORMAL_SPEED;
		}
	}
	doNothing(0);
}

void turnLeft(float rotations)
{
	resetEncoders();
	while(abs(getMotorEncoder(leftMotor))<rotations*ROTATIONS_TO_TICKS)
	{
		motor[leftMotor]=-NORMAL_SPEED;
		motor[rightMotor]=NORMAL_SPEED;
	}
	doNothing(0);
}

void turnRight(float rotations)
{
	resetEncoders();
	while(abs(getMotorEncoder(rightMotor))<rotations*ROTATIONS_TO_TICKS)
	{
		motor[leftMotor]=NORMAL_SPEED;
		motor[rightMotor]=-NORMAL_SPEED;
	}
	doNothing(0);
}

task main()
{



}
