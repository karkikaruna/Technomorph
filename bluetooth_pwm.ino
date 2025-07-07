const int motorLeft1 = 8;
const int motorLeft2 = 9;
const int motorRight1 = 10;
const int motorRight2 = 11;

const int enableLeft = 5;
const int enableRight = 6;

char command;
int speed = 200; 

void setup() {
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);

    switch (command) {
      case 'F': 
        moveForward();
        break;
      case 'B': 
        moveBackward();
        break;
      case 'L': 
        turnLeft();
        break;
      case 'R': 
        turnRight();
        break;
      case 'S': 
        stopMotors();
        break;
      case '+':
        speed = min(255, speed + 10);
        Serial.print("Speed increased to ");
        Serial.println(speed);
        break;
      case '-': 
        speed = max(0, speed - 10);
        Serial.print("Speed decreased to ");
        Serial.println(speed);
        break;
    }
  }
}

void moveForward() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}

void moveBackward() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}

void stopMotors() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
  analogWrite(enableLeft, 0);
  analogWrite(enableRight, 0);
}

void turnLeft() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
  analogWrite(enableLeft, speed / 2); 
  analogWrite(enableRight, speed);
}

void turnRight() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed / 2); 
}
