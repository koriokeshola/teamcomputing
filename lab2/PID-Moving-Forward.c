// Function for turning left
void turnLeft(long time, long motorpower)
{
	
	setMotorSpeed(motorB, -motorpower);	//Set the leftMotor (motor1) to half power (50)
	setMotorSpeed(motorC, motorpower);  //Set the rightMotor (motor6) to half power (50)
	sleep(time);						//Wait for 2 seconds before continuing on in the program.
} // End function


// Main function
task main()
{
	turnLeft(1000,50);
	
} // End main
