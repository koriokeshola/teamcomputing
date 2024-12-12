#define leftMotor 1
#define rightMotor 2

// Program is to be run in simulator

// Function for turning 90 degrees
void turn90(char direction);

// Main function
task main() 
{
    // starting co-ordinates in {x, y}, facing x
    const int start[2] = {1, 4};
    int curX = start[0];
    int curY = start[1];
    char curDirection = 'x';
    
    // Define sensors
    SensorType[S3] = sensorEV3_Color;
    SensorType[S4] = sensorEV3_Gyro;
    
    // Set target1 coordinates in {x,y}
    int target1[2] = {6, 5};
    int detected = 0; // variable for detecting target
    
    // If current x co-ordinate is less than the target's
    if (curX < target1[0]) 
    {
        // While current x co-ordinate is less than or equal to the target's
        while (curX <= target1[0]) 
        {
            // Display co-ordinates
            displayBigTextLine(4, "{ %d, %d}", curX, curY);
            
            // If colorSensor is more than 25
            if (SensorValue[S3] > 25) 
            {
                detected = 0; // Target detected is false
            } // End inner if
            else 
            {
                // If target is not detected
                if (detected == 0) 
                {
                    curX++; // Increment X co-ordinate if target is not detected
                }
                
                detected = 1; // Target detected is true
            } // End inner else
            
            // Move right at full speed
            setMotorSync(leftMotor, rightMotor, 0, 100);
        }
        
        curX--; // Decrement X co-ordinate if current X co-ordinate is less than the Target's x co-ordinate
    } // End outer if
    
    
    // If current y co-ordinate is larger than the target's
    if (curY > target1[1]) 
    {
        // Call turn90 function (turning left)
        turn90('L');
        
        // drive until curY = target1[y]
        
        // While current y co-ordinate is more than or equal to the target's
        while (curY >= target1[1]) 
        {
            // Display co-ordinates
            displayBigTextLine(4, "{ %d, %d}", curX, curY);
            
            // If colorSensor is more than 25
            if (SensorValue[S3] > 25) 
            {
                detected = 0; // Target detected is false
            } // End inner if
            else 
            {
                // If target is not detected
                if (detected == 0) 
                {
                    curY--; // Decrement Y co-ordinate if target is not detected
                } // End inner inner if
                
                detected = 1; // Target detected is true
            } // End inner else
            
            // Turn right at full speed
            setMotorSync(leftMotor, rightMotor, 0, 100);
        } // End while
        
    } // End outer if
    
    
    // If current y co-ordinate is less than the target's
    else if (curY < target1[1]) 
    {
        // Call turn90 function (turning right)
        turn90('R');
        
        // While current Y co-ordinate is less than or equal to Target 1 co-ordinates
        while (curY <= target1[1]) 
        {
            // Display co-ordinates
            displayBigTextLine(4, "{ %d, %d}", curX, curY);
            
            // If colorSensor value is more than 25
            if (SensorValue[S3] > 25) 
            {
                detected = 0; // Target detected is false
            } // End if
            else 
            {
                // If target is not detected
                if (detected == 0) 
                {
                    // Increment Y co-ordinate if target is not detected
                    curY++;
                }
                
                detected = 1; // Target detected is true
            } // End else
            
            // Turn right at full speed
            setMotorSync(leftMotor, rightMotor, 0, 100);
        } // End while
        
    } // End outer else of
} // End task main


// Function for turning 90 degrees
void turn90(char direction) 
{
    // Reset gyro to 0
    resetGyro(S4);
    
    // Check direction for rotation, char 'L' for left turn, char 'R' for right turn
    if (direction == 'l'  || direction == 'L') 
    {
        
        // Turn until 90 degrees to the left if true
        while(SensorValue[S4] < 80) 
        {
            setMotorSync(leftMotor, rightMotor, 100, 100);
        } // End while
        
    } // End if
    
    // If direction is R, turn right
    else if (direction == 'r'  || direction == 'R') 
    {
        
        // Turn until 90 degrees to the right if true
        while(SensorValue[S4] > -80) 
        {
            // Turn right at full speed
            setMotorSync(leftMotor, rightMotor, -100, 100);
        } // End while
        
    } // End else if
} // End turn90 function

// double check "setMotorSync(leftMotor, rightMotor, -100, 100);" and "setMotorSync(leftMotor, rightMotor, 0, 100);"
