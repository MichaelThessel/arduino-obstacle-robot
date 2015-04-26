/*
 * Operates a ATTiny85 robot with basic collission detection.
 */

// Pin configuration
const int leftIrPin = 2;
const int rightIrPin = 3;
const int leftMotorPin = 1;
const int rightMotorPin = 0;

// Other constants
const int motorSpeed = 100;
const int turnSpeed = 255;
const int directionLeft = 1;
const int directionRight = 0;

/**
 * Setup function
 */
void setup() {
    pinMode(leftIrPin, INPUT);
    pinMode(rightIrPin, INPUT);
    pinMode(leftMotorPin, OUTPUT);
    pinMode(rightMotorPin, OUTPUT);
}

/**
 * Loop function
 */
void loop() {
    // Wait 5s to be able to put the robot on the ground
    delay(5000);

    explore();
}

/**
 * Move around and don't crash into anything
 */
void explore() {
    while (true) {

        // Check if we got an obstacle
        if (detectObstacleLeft()) {
            turnRight();
        } else if (detectObstacleRight()) {
            turnLeft();
        } else {
            move();
        }

        delay(50);
    }
}

/**
 * Turn
 * int direction What direction to turn to
 */
void turn(int direction) {
    if (direction == directionLeft) {
        analogWrite(rightMotorPin, 0);
        analogWrite(leftMotorPin, turnSpeed);
    } else {
        analogWrite(leftMotorPin, 0);
        analogWrite(rightMotorPin, turnSpeed);
    }
}

/**
 * Turn left
 */
void turnLeft() {
    turn(directionLeft);
}

/**
 * Turn right
 */
void turnRight() {
    turn(directionRight);
}

/**
 * Move
 */
void move() {
    analogWrite(leftMotorPin, motorSpeed);
    analogWrite(rightMotorPin, motorSpeed);
}

/**
 * Check the left infrared sensor for obstacles
 */
bool detectObstacleLeft() {
    bool obstacleDetected = digitalRead(leftIrPin);
    return obstacleDetected;
}

/**
 * Check the right infrared sensor for obstacles
 */
bool detectObstacleRight() {
    bool obstacleDetected = digitalRead(rightIrPin);
    return obstacleDetected;
}
