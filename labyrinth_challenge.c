#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  rightIME,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIME,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  armIME,         sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, PIDControl, reversed, driveLeft, encoderPort, I2C_2)
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
	forward(12/WHEEL_CIRCUM);
}
