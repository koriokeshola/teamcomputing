#pragma config(Sensor, S1,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


// Main function
task main()
{
    // Move until stop button is pressed
	while(SensorValue(sonarSensor) != 0)
	{
        // Adjust motor left or right based on whether 1cm white line has been detected
		if(SensorValue(lightSensor) < 40)
		{
			setMotorSpeed(leftMotor, 0);
			setMotorSpeed(rightMotor, 20);

		}
		else if(SensorValue(lightSensor) > 40) 
        {
			setMotorSpeed(leftMotor, 20);
			setMotorSpeed(rightMotor, 0);

		} // end if statement else
        
	} // end whie loop

} // end main
