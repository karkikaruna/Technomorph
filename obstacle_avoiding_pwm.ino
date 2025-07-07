const int motorLeft1 = 8;
const int motorLeft2 = 9;
const int motorRight1 = 10;
const int motorRight2 = 11;

const int enableLeft = 5;  
const int enableRight = 6;  

const int trigPin = 3;
const int echoPin = 4;

const int threshold = 20;
long duration;
int distance;
int frontDist, leftDist, rightDist;
int motorSpeed = 100; 

void setup() {
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  analogWrite(enableLeft, motorSpeed);
  analogWrite(enableRight, motorSpeed);

  Serial.begin(9600);
}


void loop() {
  delay(500);
  moveForward();

  if (checkObstacle()) {
    moveBackward();
    delay(3000);
    stopMotors();

    turnLeft();
    delay(500);
    stopMotors();
    leftDist = getDistance();

    turnRight();
    delay(500);
    stopMotors();
    turnRight();
    delay(500);
    stopMotors();
    rightDist = getDistance();
    turnLeft();
    delay(500);
    stopMotors();

    if (leftDist > rightDist && leftDist > threshold) {
      turnLeft();
      delay(1000);
      if (!checkObstacle()) moveForward();
    } else if (rightDist > threshold) {
      turnRight();
      delay(1000);
      if (!checkObstacle()) moveForward();
    } else {
      moveBackward();
      delay(1000);
      stopMotors();
    }
  } else {
    moveForward();
  }
}


bool checkObstacle() {
  int dist = getDistance();
  return (dist <= threshold); 
}


void moveForward() {
  analogWrite(enableLeft, motorSpeed);
  analogWrite(enableRight, motorSpeed);

  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
}

void moveBackward() {
  analogWrite(enableLeft, motorSpeed);
  analogWrite(enableRight, motorSpeed);

  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
}

void stopMotors() {
  analogWrite(enableLeft, 0);
  analogWrite(enableRight, 0);

  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
}

void turnLeft() {
  analogWrite(enableLeft, motorSpeed);
  analogWrite(enableRight, motorSpeed);

  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
}

void turnRight() {
  analogWrite(enableLeft, motorSpeed);
  analogWrite(enableRight, motorSpeed);

  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); 
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

