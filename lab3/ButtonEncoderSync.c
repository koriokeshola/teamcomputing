#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)  // configure left motor
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)  // configure right motor


void drive(long nMotorRatio, long dist, long power);  // function to drive the robot
void reset();  // function to reset encoders

#define circumference 17.6  // constant for circumference of the wheel


// Main function
task main()  
{
	int distance = 0;  // variable to store distance
	int power = 0;  // variable to store power

	while(getButtonPress(buttonEnter) == 0)  // loop until enter button is pressed
	{
		displayBigTextLine(4, "%d cm distance", distance);  // display current distance

		if (getButtonPress(buttonUp))  // if up button is pressed
		{
			distance = 10;  // set distance to 10
		}
		else if (getButtonPress(buttonDown))  // if down button is pressed
		{
			distance = 40;  // set distance to 40
		}
		else if (getButtonPress(buttonLeft))  // if left button is pressed
		{
			distance = 60;  // set distance to 60
		}
		else if (getButtonPress(buttonRight))  // if right button is pressed
		{
			distance = 80;  // set distance to 80
		}
	}

	while(power < 10)  // loop until power is greater than or equal to 10
	{
		power = random(100);  // generate random power value (0-99)
	}

	drive(0, distance, power);  // call drive function with specified parameters
    
} // End main


// Reset encoders
void reset()
{
	resetMotorEncoder(leftMotor);  // reset left motor encoder
	resetMotorEncoder(rightMotor);  // reset right motor encoder
    
} // End function


// Drive a distance at a ratio, to a set power level
void drive(long nMotorRatio, long dist, long power)
{
	float rotations = 360 * (dist / circumference);  // calculate rotations based on distance

	reset();  // reset encoders

	setMotorSyncEncoder(leftMotor, rightMotor, nMotorRatio, rotations, power);  // set motors to drive specific distance at specified power
	waitUntilMotorStop(leftMotor);  // wait until left motor stops
    
} // End function
