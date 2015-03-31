/*
 * Operates a ATTiny85 based robot that has basic collission detection.
 */

const int ledPin = 3;
const int irPin = 4;
const int leftMotorPin = 0;
const int rightMotorPin = 1;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);

  flashLed(10, 200); // Booting up; flash led
}

void loop() {
  explore();
}

// Drive around and don't crash into anything
void explore() {
  int obstacleDetected = 0;
  drive(); // Start driving

  while (true) {
    // Check if we got an obstacle
    obstacleDetected = detectObstacle();

    // Show obstacle status with the led
    digitalWrite(ledPin, obstacleDetected);

    if (obstacleDetected) {
      turn();
    } else {
      drive();
    }
  }
}

// Turn the robot randomly
void turn() {
  int direction = millis() & 1;

  while(detectObstacle()) {
    digitalWrite(leftMotorPin, direction);
    digitalWrite(rightMotorPin, direction ^ 1);

    delay(50);
  }
}

// Drive
void drive() {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);

  delay(100);
}

// Check the infrared sensor for obstacles
int detectObstacle() {
  int obstacleDetected = digitalRead(irPin);
  obstacleDetected = obstacleDetected ^ 1; // Invert
  return obstacleDetected;
}


// Flash the led
void flashLed(int flashes, int delayMs) {
  while (flashes) {
    flashes--;
    digitalWrite(ledPin, HIGH);
    delay(delayMs);
    digitalWrite(ledPin, LOW);
    delay(delayMs);
  }
}
