#pragma config(Sensor, S1,     ultraSonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Function to drive the robot until it detects a line
void driveUntilLine();


// main task
task main()
{
	// call the function to drive until line detection
	driveUntilLine();
    
} // End main


// function definition to drive the robot until it detects a line
void driveUntilLine()
{
	// variables to store line detection count and detection flag
	int line = 0
    int detected = 0;

	// continuous loop to drive until line detection
	while(1)
	{
		// display message prompting to press enter to end
		displayBigTextLine(4, "Enter to end");
        
		// display the number of lines detected
		displayBigTextLine(7, "Lines: %d", line);

		// check if enter button is pressed to stop the program
		if(getButtonPress(buttonEnter) == 1) 
        {
            stopAllTasks();
        } // End if

		// check light sensor value to detect a line
		if (SensorValue(lightSensor) > 20)
		{
			// reset detection flag and move forward at a slow speed
			detected = 0;
			setMotorSync(leftMotor, rightMotor, 0, 20);
		}
		else
		{
			// if line is detected
			if (detected == 0) 
            {
                line++; // increment line count if line is first detected
            } // End if
			detected = 1; // set detection flag

			// stop the motors and wait for 0.5 seconds
			setMotorSync(leftMotor, rightMotor, 0, 0);
			sleep(500);

			// move forward until a line is detected again
			while(SensorValue(lightSensor) < 20)
			{
				// check if enter button is pressed to stop the program
				if(getButtonPress(buttonEnter) == 1)
                {
                    stopAllTasks();
                } // End if

				// move forward at a slow speed
				setMotorSync(leftMotor, rightMotor, 0, 5);
                
			} // End inner while
            
		} // End if else
        
	} // End outer while
    
} // End function
