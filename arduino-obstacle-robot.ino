/*
 * Operates a ATTiny85 based robot that has basic collission detection.
 */

// Pin configuration
const int ledPin = 3;
const int irPin = 4;
const int leftMotorPin = 0;
const int rightMotorPin = 1;

// Other constants
const int motorSpeed = 100;
const int directionLeft = 1;
const int directionRight = 0;

/**
 * Setup function
 */
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  analogWrite(leftMotorPin, 0);
  analogWrite(rightMotorPin, 0);

  flashLed(20, 100); // Booting up; flash led
}

/**
 * Loop function
 */
void loop() {
  explore();
}

/**
 * Drive around and don't crash into anything
 */
void explore() {
  int obstacleDetected = 0;

  while (true) {
    // Check if we got an obstacle
    obstacleDetected = detectObstacle();

    // Show obstacle status with the led
    digitalWrite(ledPin, obstacleDetected);

    if (obstacleDetected) {
        stop();
        turnRandom();
    } else {
        drive(100);
    }
  }
}

/**
 * Turn the robot randomly
 */
void turnRandom() {
  int direction = millis() & 1;
  int turnTime = 50;

  while(detectObstacle()) {
    if (direction == directionLeft) {
        turnLeft(turnTime);
    }
    else {
        turnRight(turnTime);
    }
  }
}

/**
 * Turn left
 * int turnTime How long to turn for
 * int direction What direction to turn to
 */
void turn(int turnTime, int direction) {
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
 * Drive
 * int driveTime Time to drive for
 */
void drive(int driveTime) {
  analogWrite(leftMotorPin, motorSpeed);
  analogWrite(rightMotorPin, motorSpeed);

  delay(driveTime);
}

/**
 * Stop
 */
void stop() {
  analogWrite(leftMotorPin, 0);
  analogWrite(rightMotorPin, 0);
}

/**
 * Check the infrared sensor for obstacles
 */
bool detectObstacle() {
  bool obstacleDetected = digitalRead(irPin);
  return !obstacleDetected;
}

/**
 * Flash the led
 * int flashes How many times to flash
 * int delayMs Ms interval
 */
void flashLed(int flashes, int delayMs) {
  while (flashes) {
    flashes--;
    digitalWrite(ledPin, HIGH);
    delay(delayMs);
    digitalWrite(ledPin, LOW);
    delay(delayMs);
  }
}
