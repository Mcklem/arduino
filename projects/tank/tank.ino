int pwmA = 3;
int pwmB = 11;
int pA = 5;
int pB = 6;
int pC = 8;
int pD = 10;
int MOTOR_POW = 255;

void setup() {
  Serial.begin(9600);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
  pinMode(pC, OUTPUT);
  pinMode(pD, OUTPUT);
}

void loop() {
 Serial.println("Forward");
  moveForwardLeftTrack();
  moveForwardRightTrack();
  delay(10000);
  Serial.println("Stop");
  stopMove();
  delay(500);
  Serial.println("Backward");
  moveBackwardLeftTrack();
  moveBackwardRightTrack();
  delay(10000);
  Serial.println("Stop");
  stopMove();
  delay(500);
}

void moveForwardLeftTrack(){
  analogWrite(pwmA, MOTOR_POW); 
  digitalWrite(pA, 1); 
  digitalWrite(pB, 0); 
}

void moveBackwardLeftTrack(){
  analogWrite(pwmA, MOTOR_POW); 
  digitalWrite(pA, 0); 
  digitalWrite(pB, 1); 
}

void moveForwardRightTrack(){
  analogWrite(pwmB, MOTOR_POW); 
  digitalWrite(pC, 1); 
  digitalWrite(pD, 0); 
}

void moveBackwardRightTrack(){
  analogWrite(pwmB, MOTOR_POW); 
  digitalWrite(pC, 0); 
  digitalWrite(pD, 1); 
}

void stopMove(){
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0); 
  digitalWrite(pA, 0); 
  digitalWrite(pB, 0); 
  digitalWrite(pC, 0); 
  digitalWrite(pD, 0); 
  delay(25);
}

