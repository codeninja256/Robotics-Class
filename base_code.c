//Base code for moving forward and turning

#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl11, armEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  rightIME,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIME,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  armIME,         sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, PIDControl, reversed, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, PIDControl, driveRight, encoderPort, I2C_1)

const float NORMAL_SPEED=63;
const float SLOW_SPEED=40;
const float ROTATIONS_TO_TICKS=627.2;
const int AXLE_LENGTH=11;
const int WHEEL_DIAMETER=4;
const float WHEEL_CIRCUM=WHEEL_DIAMETER*PI;

void resetEncoders();
void doNothing(int ms);
void forward(float rotations);
void turnLeft(float rotations);
void turnRight(float rotations);
void closeClaw(); //arm and claw for my robot don't have encoders, so we need to use time here
void openClaw();
void moveArmUp(float time); 
void moveArmDown(float time);

void resetEncoders()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
}

void doNothing(int ms)
{
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	motor[clawMotor]=0;
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

void closeClaw()
{
		motor[clawMotor] = -20;
   	wait1Msec(1400);
   	doNothing(0);
}
void openClaw()
{
	  motor[clawMotor]=20;
	  wait1Msec(1400);
	  doNothing(0);
}

void moveArmUp(float time)
{
	motor[armMotor]=40;
	wait1Msec(time);
}

void moveArmDown(float time)
{
		motor[armMotor]=-40;
		wait1Msec(time);
}

task main()
{
	//TODO: Call functions in here


}
