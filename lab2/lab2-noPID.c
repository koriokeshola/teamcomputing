#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, openLoop, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, openLoop, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will move your robot make a series of moves for different lengths of time.
  At the end of the program, all motors will shut down automatically and turn off.

                            ROBOT CONFIGURATION: LEGO EV3 REM Bot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                [Description]
    MotorC        	leftMotor           LEGO EV3 Motor	  Left side motor
    MotorB       	rightMotor          LEGO EV3 Motor	  Right side motor (reversed)
------------------------------------------------------------------------------------------------*/

// Function for turning robot left
void turn90degreesLeft()
{
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);
	sleep(5000); // Move forward at half power for 5 seconds

	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	sleep(2000); // Stay still for 2 seconds

	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, -50);
	sleep(500); // Turn left at half power for .5 seconds
    
} // End function


// Function for turning robot right
void turn90degreesRight()
{
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);
	sleep(5000); // Move forward at half power for 5 seconds

	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	sleep(2000); // Stay still for 2 seconds

	setMotorSpeed(leftMotor, -50);
	setMotorSpeed(rightMotor, 50);
	sleep(500); // Turn right at half power for .5 seconds

} // End function


// Function for going forward 1 second at half power for 1 second
void goForward1second()
{
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);
	sleep(1000);

} // End function


// Function for swinging to the right
void swingRight90degrees()
{
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);
	sleep(1000); // Go forward at half power for 1 second

	setMotorSpeed(leftMotor, -50);
	setMotorSpeed(rightMotor, 50);
	sleep(500); // Turn to the right at half power for .5 seconds

} // End function


// Function for swinging to the left
void swingLeft90degrees()
{
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);
	sleep(1000); // Go forward at half power for 1 second

	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, -50);
	sleep(500); // Turn to the left at half power for .5 seconds

} // End function


// Function for reversing for 1 second
void reverse1second()
{
	setMotorSpeed(leftMotor, -50);
	setMotorSpeed(rightMotor, -50);
	sleep(1000); // Move backwards at half power for 1 second

} // End function


// Main function
task main()
{
    // Comment out functions accordingly to test individually
    turn90degreesLeft();
	turn90degreesRight();
    goForward1second();
    swingRight90degrees();
    swingLeft90degrees();
    reverse1second();
    
} // End main
