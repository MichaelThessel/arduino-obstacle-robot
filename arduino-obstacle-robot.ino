/*
 * Operates a ATTiny85 robot with basic collission detection.
 */

// Pin configuration
const int leftIrPin = 2;
const int rightIrPin = 3;
const int leftMotorPin = 1;
const int rightMotorPin = 0;

// Other constants
const int motorSpeed = 150;
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
            turnRight(1000);
        } else if (detectObstacleRight()) {
            turnLeft(1000);
        } else {
            move(50);
        }
    }
}

/**
 * Turn
 * int turnTime How long to turn for
 * int direction What direction to turn to
 */
void turn(int turnTime, int direction) {
    stop();

    if (direction == directionLeft) {
        analogWrite(leftMotorPin, motorSpeed);
    } else {
        analogWrite(rightMotorPin, motorSpeed);
    }
    delay(turnTime);
}

/**
 * Turn left
 * int turnTime How long to turn for
 */
void turnLeft(int turnTime) {
    turn(turnTime, directionLeft);
}

/**
 * Turn right
 * int turnTime How long to turn for
 */
void turnRight(int turnTime) {
    turn(turnTime, directionRight);
}

/**
 * Move
 * int moveTime Time to move for
 */
void move(int moveTime) {
    analogWrite(leftMotorPin, motorSpeed);
    analogWrite(rightMotorPin, motorSpeed);

    delay(moveTime);
}

/**
 * Stop
 */
void stop() {
    analogWrite(leftMotorPin, 0);
    analogWrite(rightMotorPin, 0);
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
