#pragma config(Sensor, S1,     ultraSonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Functions
void trackLine();
void avoidObstacle();
void resetEncoders();


// Main function
task main()
{
	trackLine();
    
} // End main


// Function for tracking line
void trackLine()
{
    // Continuous loop to drive until line detection
	while(1)
	{
        // Exit program if enter is pressed
        displayBigTextLine(4, "Enter to end");

        // Stop all tasks if enter button is pressed
        if(getButtonPress(buttonEnter) == 1)
        {
            stopAllTasks();
        } // End if

        // Avoid obstacle when close
        if (getUSDistance(ultraSonic) < 10)
        {
            avoidObstacle();
        } // End if

        // Turn left if dark detected, else turn right
        if(SensorValue(lightSensor) < 25)
        {
            setMotorSync(leftMotor, rightMotor, -25, 25);
        }
        else
        {
            setMotorSync(leftMotor, rightMotor, 25, 25);
        } // End if else

    } // End while
    
} // End function


// Function for avoiding an obstacle
void avoidObstacle()
{
	// Turn left 90 degrees
	resetEncoders();
	setMotorSyncEncoder(leftMotor, rightMotor, -100, 180, 25);
	waitUntilMotorStop(leftMotor);

    // Move forward at at 20 speed for 2 seconds
	setMotorSync(leftMotor, rightMotor, 0, 20);
	sleep(2000);

	// Turn right 90 degrees
	resetEncoders();
	setMotorSyncEncoder(leftMotor, rightMotor, 100, 180, 25);
	waitUntilMotorStop(leftMotor);

    // Move forward at at 20 speed for 4 seconds
	setMotorSync(leftMotor, rightMotor, 0, 20);
	sleep(4000);

	// Turn right 90 degrees
	resetEncoders();
	setMotorSyncEncoder(leftMotor, rightMotor, 100, 180, 25);
	waitUntilMotorStop(leftMotor);
    
    // Move forward at at 20 speed for 2 seconds
	setMotorSync(leftMotor, rightMotor, 0, 20);
	sleep(2000);

	// Turn left 90 degrees
	resetEncoders();
	setMotorSyncEncoder(leftMotor, rightMotor, -100, 180, 25);
	waitUntilMotorStop(leftMotor);
    
} // End function


// Function for resetting motors
void resetEncoders()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
    
} // End function