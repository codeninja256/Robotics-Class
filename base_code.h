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

#ifndef BASE_CODE_H
#define BASE_CODE_H

//Base code for moving forward and turning

//--COMMENT OUT THE FOLLOWING LINE TO USE GYRO FOR TURNING (NOT RECOMMENDED)--
#define USE_ENCODERS 

const float NORMAL_SPEED = 63;
const float SLOW_SPEED = 40;
const float ROTATIONS_TO_TICKS = 627.2;
const int WHEEL_DIAMETER = 4;
const float WHEEL_CIRCUM = WHEEL_DIAMETER * PI;
const int AXLE_LENGTH = 12;

void resetEncoders();
void doNothing(int ms);
void forward(float rotations);
void backward(float rotations);
void turnLeft(float deg);
void turnRight(float deg);
void closeClaw();
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
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[clawMotor] = 0;
	motor[armMotor] = 0;
	wait1Msec(ms);
}

void forward(float rotations)
{
	resetEncoders();
	while(abs(getMotorEncoder(rightMotor)) < rotations * ROTATIONS_TO_TICKS && abs(getMotorEncoder(leftMotor)) < rotations * ROTATIONS_TO_TICKS)
	{
		if(abs(getMotorEncoder(rightMotor)) < abs(getMotorEncoder(leftMotor))) //if leftMotor has gone farther...
		{
			motor[rightMotor] = NORMAL_SPEED; //...run rightMotor at normal speed
			motor[leftMotor] = SLOW_SPEED; //...slow down leftMotor
		}
		if(abs(getMotorEncoder(rightMotor)) > abs(getMotorEncoder(leftMotor))) //if rightMotor has gone farther...
		{
			motor[rightMotor] = SLOW_SPEED; //...slow down rightMotor
			motor[leftMotor] = NORMAL_SPEED; //...run leftMotor at normal speed
		}
		if(abs(getMotorEncoder(rightMotor)) == abs(getMotorEncoder(rightMotor))) //if rightMotor and leftMotor have gone the same distance...
		{
			motor[rightMotor] = NORMAL_SPEED; //...run rightMotor at normal speed
			motor[leftMotor] = NORMAL_SPEED; //...run leftMotor at normal speed
		}
	}
	motor[rightMotor] = 0; //stop motors
	motor[leftMotor] = 0;
}

void backward(float rotations)
{
	resetEncoders();
	while(abs(getMotorEncoder(rightMotor)) < rotations * ROTATIONS_TO_TICKS && abs(getMotorEncoder(leftMotor)) < rotations * ROTATIONS_TO_TICKS)
	{
		if(abs(getMotorEncoder(rightMotor)) < abs(getMotorEncoder(leftMotor))) //if leftMotor has gone farther...
		{
			motor[rightMotor] = -NORMAL_SPEED; //run rightMotor at normal speed
			motor[leftMotor] = -SLOW_SPEED; //slow down leftMotor
		}
		if(abs(getMotorEncoder(rightMotor)) > abs(getMotorEncoder(leftMotor))) //if rightMotor has gone farther...
		{
			motor[rightMotor] = -SLOW_SPEED; //slow down rightMotor
			motor[leftMotor] = -NORMAL_SPEED; //run leftMotor at normal speed
		}
		if(abs(getMotorEncoder(rightMotor)) == abs(getMotorEncoder(rightMotor))) //if rightMotor and leftMotor have gone the same distance
		{
			motor[rightMotor] = -NORMAL_SPEED; //run rightMotor at normal speed
			motor[leftMotor] = -NORMAL_SPEED; //run leftMotor at normal speed
		}
	}
	motor[rightMotor] = 0; //stop motors
	motor[leftMotor] = 0;
}

void turnLeft(float deg)
{
#ifdef USE_ENCODERS
	resetEncoders();
	float rotations = (PI * AXLE_LENGTH * deg / 360) / (WHEEL_DIAMTER * PI);
	while(abs(getMotorEncoder(leftMotor)) < rotations * ROTATIONS_TO_TICKS)
	{
		motor[leftMotor] = -NORMAL_SPEED;
		motor[rightMotor] = NORMAL_SPEED;
	}
#else
	wait1Msec(1000);
	while(SensorValue(gyro) > -deg * 10)
	{
		motor[leftMotor] = -NORMAL_SPEED;
		motor[rightMotor] = NORMAL_SPEED;
	}
#endif
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void turnRight(float deg)
{
#ifdef USE_ENCODERS
	resetEncoders();
	float rotations = (PI * AXLE_LENGTH * deg / 360) / (WHEEL_DIAMTER * PI);
	while(abs(getMotorEncoder(rightMotor)) < rotations * ROTATIONS_TO_TICKS)
	{
		motor[leftMotor] = NORMAL_SPEED;
		motor[rightMotor] = -NORMAL_SPEED;
	}
#else
	wait1Msec(1000);
	while(SensorValue[gyro] < deg * 10)
	{
		motor[leftMotor] = NORMAL_SPEED;
		motor[rightMotor] = -NORMAL_SPEED;
	}
#endif
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void closeClaw()
{
	motor[clawMotor] = -20;
	wait1Msec(1400);
	motor[clawMotor] = 0;
}

void openClaw()
{
	motor[clawMotor] = 40;
	wait1Msec(1400);
	motor[clawMotor] = 0;
}

void moveArmUp(float time)
{
	motor[armMotor] = 40;
	wait1Msec(time);
	motor[armMotor] = 0;
}

void moveArmDown(float time)
{
	motor[armMotor] = -40;
	wait1Msec(time);
	motor[armMotor] = 0;
}

#endif
