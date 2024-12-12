#define leftMotor 1
#define rightMotor 2


// Program functions
void turn90(char direction);
void driveTarget1(int *curX, int *curY);
void driveTarget2(int *curX, int *curY);
int driveToX(int targetX, int *curX);
void driveToY(int targetY, int *curY);
void updateDirection(int *curDirection, int newDirection);
void faceDirection(int newDirection, int curDirection);
void setStop();
void waitBeep();


// Starting Position
int curX = 3;
int curY = 1;

// Cardinal Coordinates, 0 for North, 1 for East, 2 for South, 3 for West
int startDirection = 1;
int curDirection = 1;


// Main function
task main()
{
	
	SensorType[S3] = sensorEV3_Color;
	SensorType[S4] = sensorEV3_Gyro;
	
	// Drive to 1st target
	driveTarget1(&curX, &curY);
	
	// Stop robot, to prevent bug
	setStop();
	
	// Play beep sound while waiting
	waitBeep();
	
	// Drive to 2nd target
	driveTarget2(&curX, &curY);
	
} // End main


// Function for turning 90 degrees
// 'L' for left, 'R' for right
void turn90(char direction)
{
	// Reset gyro to 0
	resetGyro(S4);
	
	// Check direction for rotation, if L turn left
	if (direction == 'l'  || direction == 'L')
	{
		
		// Turn until turned left
		while(SensorValue[S4] < 80)
		{
			setMotorSync(leftMotor, rightMotor, 100, 100);
		} // End while
		
		// Update co-ordinates as the robot is now facing a different direction
		updateDirection(&curDirection, -1);
	}
	// If Direction is R, turn right
	else if (direction == 'r'  || direction == 'R')
	{
		
		// Turn until turned right
		while(SensorValue[S4] > -80)
		{
			setMotorSync(leftMotor, rightMotor, -100, 100);
		} // End while
		
		// Update co-ordinates as the robot is now facing a different direction
		updateDirection(&curDirection, 1);
	} // End if else
	
} // End function


// Function for driving robot to first target
void driveTarget1(int *curX, int *curY)
{
	// Set target co-ordinates
	int target1[2] = {3, 7};
	
	// Drive to target X co-ordinate
	driveToX(target1[0], curX);
	
	// Stop robot, to prevent bug
	setStop();
	
	// Sleep for 0.1 seconds
	sleep(100);
	
	// Drive to target Y co-ordinate
	driveToY(target1[1], curY);
	
} // End function


// Function for driving robot to second target
void driveTarget2(int *curX, int *curY)
{
	// Set target co-ordinates
	int target2[2] = {1, 1};
	
	// Drive to target Y co-ordinate
	driveToX(target2[0], curX);
	
	// Stop robot, to prevent bug
	setStop();
	
	// Sleep for 0.1 seconds
	sleep(100);
	
	// Drive to target Y co-ordinate
	driveToY(target2[1], curY);
	
} // End function


// Function to go to an X coordinate
int driveToX(int targetX, int *curX)
{
	int detected = 0;
	
	// Return 0 if robot is already at target X co-ordinate
	if (*curX == targetX)
	{
		return 0;
	} // End if
	
	// If the current X co-ordinate is less than the target
	if (*curX > targetX)
	{
		// Set desired direction to west
		faceDirection(3, curDirection);
		
		// Drive to target X co-ordinate
		while (*curX >= targetX)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", *curX, curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Decrement current X co-ordinate if target has been detected
				if (detected == 0)
				{
					(*curX)--;
				}
				
				// Target detected is now true
				detected = 1;
			} // End inner if else
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		} // End while
		
		// Adjust current X co-ordinate by incrementing
		(*curX)++;
	}
	else 
	{
		// Set desired direction to east
		faceDirection(1, curDirection);
		
		// Drive to target X co-ordinate
		while (*curX <= targetX)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", *curX, curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Increment current X co-ordinate if target has been detected
				if (detected == 0)
				{
					(*curX)++;
				}
				
				// Target detected is now true
				detected = 1;
			}
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		} // End while
		
		// Adjust current X co-ordinate by decrementing
		*(curX)--;
	}
	
	return 0;
} // End function


// Function to go to a y coordinate
void driveToY(int targetY, int *curY)
{
	int detected = 0;
	
	// If current y is greater than the target y
	if (*curY > targetY)
	{
		
		// Turn based on current facing direction
		if (curDirection == 1)
		{
			turn90('L');
		}
		else
		{
			turn90('R');
		} // End inner if else
		
		
		// drive until curY = target y
		while (*curY >= targetY)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", curX, *curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Decrement current Y co-ordinate if target has been detected
				if (detected == 0)
				{
					(*curY)--;
				}
				
				// Target detected is now true
				detected = 1;
			}
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		}
		
		// Adjust current Y co-ordinate by incrementing
		(*curY)++;
	}
	// Otherwise, it is less than, turn right
	else if (*curY < targetY)
	{
		// Turn left or right based on current facing direction
		if (curDirection == 1)
		{
			turn90('R');
		}
		else
		{
			turn90('L');
		}
		
		// Drive until target
		while (*curY <= targetY)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", curX, *curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Increment current Y co-ordinate after detecting target
				if (detected == 0)
				{
					(*curY)++;
				}
				
				detected = 1;
			}
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		} // End while
		
		// Adjust current Y co-ordinate by decrementing
		(*curY)--;
		
	} // End outer if else
	
} // End function


// Function for updating the current direction
void updateDirection(int *curDirection, int newDirection)
{
	// Resetting directional logic, modulus 4 is used as there are 4 directions
	*curDirection = (*curDirection + newDirection) % 4;
	
	// If value is negative, increment by 4 until positive
	if (*curDirection < 0)
	{
		*curDirection += 4;
	} // End if
		
} // End function


// Function for getting the robot to face a desired direction
void faceDirection(int newDirection, int curDirection)
{
	// Turn right if the current direction is less than the desired, increment the current direction after
	while (curDirection < newDirection) 
	{
		turn90('r');
		curDirection++;
	} // End while
	
	// Turn left if the current direction is more than the desired, decrement the current direction
	while (curDirection > newDirection) 
	{
		turn90('l');
		curDirection--;
	} // End while
	
} // End function


// Function for playing beep sound
void waitBeep()
{
	// Play beep sound
	for (int i = 0; i < 5; i++) 
	{
		playTone(1000, 1000);
		sleep(1000);
	} // End for
	
} // End function


// Function for stopping the motors
void setStop()
{
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	
} // End function
