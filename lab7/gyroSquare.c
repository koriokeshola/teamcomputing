#pragma config(Sensor, S1,     ultraSonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     lightSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Motor,  motorA,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Define the circumference of the wheel
#define circumference 17.6

// Function Prototypes
int getUserDistance();
void driveSquare(int distance);
void driveForward(int distance, int power);
void turnRight();
void resetEncoders();


// Main function
task main()
{
    // Get user input for distance
    int distance = getUserDistance();

    // Drive in a square with given distance
    driveSquare(distance);
    
} // End main


// Function to get distance from the user and return it
int getUserDistance()
{
    // Default distance
    int distance = 10;

    // While user has not pressed Enter Button (ie. for the robot to start driving)
    while(getButtonPress(buttonEnter) == 0)
    {
        // Display current selection
        displayBigTextLine(4, "%d cm perimeter", distance);

        // Choose distance using buttons
        if (getButtonPress(buttonUp))
        {
            distance = 10;
        }
        else if (getButtonPress(buttonDown))
        {
            distance = 40;
        }
        else if (getButtonPress(buttonLeft))
        {
            distance = 60;
        }
        else if (getButtonPress(buttonRight))
        {
            distance = 80;
        } // End else if
    }
    
    return distance;
    
} // End function


// Function to drive the robot in a square
void driveSquare(int distance)
{
    // Loop for each side of a square (4 times)
    for (int i = 0; i < 4; i++)
    {
        // Drive forward the given distance
        driveForward(distance, 25);

        // Turn 90 degrees to the right
        turnRight();
    } // End for
    
} // End function


// Function to drive the robot forward for a given distance
void driveForward(int distance, int power)
{
    // Calculate the number of rotations needed to travel the given distance
    float rotations = 360 * (distance / circumference);

    // Reset encoders for accuracy
    resetEncoders();
    
    // Drive until the encoder hits the calculated rotations
    setMotorSyncEncoder(leftMotor, rightMotor, 0, rotations, power);
    waitUntilMotorStop(leftMotor);
    
} // End function


// Function to turn the robot 90 degrees (to the right)
void turnRight()
{
    // Reset Gyro sensor to 0
    resetGyro(gyroSensor);

    // Turn until approximately 90 degrees
    while(SensorValue[gyroSensor] < 85)
    {
        setMotorSync(leftMotor, rightMotor, 100, 25);
    } // End while
    
} // End function


// Function for resetting motor encoders
void resetEncoders()
{
    resetMotorEncoder(leftMotor);
    resetMotorEncoder(rightMotor);
    
} // End function
