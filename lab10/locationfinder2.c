#define leftMotor 1
#define rightMotor 2

// Program Functions
void turn90(char direction);
int* getUserInput();
int driveToX(int targetX, int curX);
int driveToY(int targetY, int curY);
void updateDirection(int *curDirection, int newDirection);
void faceStartDirection(int startDirection, int curDirection);

int curX = 3; // Start Position - X
int curY = 1; // Start Position - Y
int startDirection = 1; // Coordinates - 0 for North, 1 for East, 2 for South, 3 for West
int curDirection = 1; // Current direction - East

// Main function
task main()
{
	SensorType[S3] = sensorEV3_Color;
	SensorType[S4] = sensorEV3_Gyro;
	
	int *target; // Target 1 co-ordinates
	int detected = 0; // Whether or not the target has been detected
	
	// Prompt user input for target
	target = getUserInput();
	
	// Go to target coordinates
	curX = driveToX(target[0], curX);
	curY = driveToY(target[1], curY);
	
	// Face the starting direction
	faceStartDirection(startDirection, curDirection);
	
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
		}
		
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
		}
		
		// Update co-ordinates as the robot is now facing a different direction
		updateDirection(&curDirection, 1);
	}
} // End function


// Take user input and return co-ordinates
int* getUserInput()
{
	// Initialise default target (origin) prior to user input
	int tempTarget[2] = {0, 0};
	
	// While enter button has not been pressed
	while(getButtonPress(buttonEnter) == 0)
	{
		// Display target co-ordinates
		displayBigTextLine(4, "Target: {%d, %d}", tempTarget[0], tempTarget[1]);
		
		// Choosing target - increment Y for Up, X for Right, decrement Y for Down, X for Left
		if (getButtonPress(buttonUp))
		{
			tempTarget[1] += 1;
			sleep(100);
		}
		else if (getButtonPress(buttonDown))
		{
			tempTarget[1] -= 1;
			sleep(100);
		}
		else if (getButtonPress(buttonLeft))
		{
			tempTarget[0] -= 1;
			sleep(100);
		}
		else if (getButtonPress(buttonRight))
		{
			tempTarget[0] += 1;
			sleep(100);
		}
	}
	
	return tempTarget;
	
} // End function


// Function for driving to X coordinate
int driveToX(int targetX, int curX)
{
	int detected = 0;
	
	// If the current X coordinate is less than the target
	if (curX < targetX)
	{
		// Drive to target
		while (curX <= targetX)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", curX, curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			} // End if
			else
			{
				// Increment current X co-ordinate
				if (detected == 0)
				{
					// Play sound to signal detection
					playTone(1000, 2);
					curX++;
				}
				
				// Target detected is true
				detected = 1;
			} // End else if
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		} // End outer if
		
		// Decrement current X co-ordinate
		curX--;
	}
	
	return curX;
}

// Function for driving to Y co-ordinate
int driveToY(int targetY, int curY)
{
	int detected = 0;
	
	// If the current Y co-ordinate is larger than the target Y co-ordinate
	if (curY > targetY)
	{
		// Turn left
		turn90('L');
		
		// Drive until current Y = target Y
		while (curY >= targetY)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", curX, curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Decrement current Y co-ordinate
				if (detected == 0)
				{
					// Play sound to signal detection
					playTone(1000, 2);
					curY--;
				}
				
				// Target detected is true
				detected = 1;
			} // End inner else if
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		}
		
	} // End outer if
	
	// Otherwise turn right
	else if (curY < targetY)
	{
		// Turn right
		turn90('R');
		
		// Drive until target
		while (curY <= targetY)
		{
			// Display current co-ordinates
			displayBigTextLine(6, "Current: {%d, %d}", curX, curY);
			
			// If sensor has not detected the target
			if (SensorValue[S3] > 25) 
			{
				detected = 0;
			}
			else
			{
				// Increment current Y co-ordinate
				if (detected == 0)
				{
					// Play sound to signal detection
					playTone(1000, 2);
					curY++;
				}
				
				// Target detected is true
				detected = 1;
			} // End inner else if
			
			// Drive forward
			setMotorSync(leftMotor, rightMotor, 0, 100);
		}
	} // End outer else if
	
	return curY;
	
} // End function


// Function for updating the current co-ordinates
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


// Function for getting the robot to face the starting direction (east)
void faceStartDirection(int startDirection, int curDirection)
{
	// Until current direction is not less than east, turn right & increment current direction
	while (curDirection < startDirection) 
	{
		turn90('r');
		curDirection++;
	} // End while
	
	// Until current direction is not more than east, turn left & decrement current direction
	while (curDirection > startDirection) 
	{
		turn90('l');
		curDirection--;
	} // End while
	
} // End function
