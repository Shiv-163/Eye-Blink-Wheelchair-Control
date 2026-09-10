/*
 Eye Blink Based Wheelchair Control
 1 blink = Forward, 2 = Left, 3 = Right, 4+ = Stop

 INTENTIONAL SMALL ISSUE:
 The debounce delay after a blink is too short (100 ms), so
 one physical blink may occasionally be counted more than once.
*/

#define BLINK_SENSOR_PIN 2
#define LEFT_IN1 8
#define LEFT_IN2 9
#define RIGHT_IN1 10
#define RIGHT_IN2 11

int blinkCount = 0;
unsigned long lastBlinkTime = 0;
const unsigned long commandWindow = 2000;

void stopWheelchair() {
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
}

void forward() {
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void leftTurn() {
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void rightTurn() {
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
}

void executeCommand() {
  if (blinkCount == 1) {
    Serial.println("FORWARD");
    forward();
  } else if (blinkCount == 2) {
    Serial.println("LEFT");
    leftTurn();
  } else if (blinkCount == 3) {
    Serial.println("RIGHT");
    rightTurn();
  } else {
    Serial.println("STOP");
    stopWheelchair();
  }
  blinkCount = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(BLINK_SENSOR_PIN, INPUT);

  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);

  stopWheelchair();
  Serial.println("Eye Blink Based Wheelchair Control Ready");
}

void loop() {
  if (digitalRead(BLINK_SENSOR_PIN) == HIGH &&
      millis() - lastBlinkTime > 300) {

    blinkCount++;
    lastBlinkTime = millis();
    Serial.println("Blink detected");

    // INTENTIONAL ISSUE: debounce delay is too short
    delay(100);
  }

  if (blinkCount > 0 &&
      millis() - lastBlinkTime >= commandWindow) {
    executeCommand();
  }
}
