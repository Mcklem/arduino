int pwm = 3;
int pA = 5;
int pB = 6;
int MOTOR_POW = 255;

void setup() {
  Serial.begin(9600);
  pinMode(pwm, OUTPUT);
  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("Forward");
  moveForward();
  delay(1000);
  stopMove();
  Serial.println("Backward");
  moveBackward();
  delay(1000);
  Serial.println("Stop");
  stopMove();
  delay(1000);
}

void moveForward(){
  analogWrite(pwm, MOTOR_POW); 
  digitalWrite(pA, 1); 
  digitalWrite(pB, 0); 
}

void moveBackward(){
  analogWrite(pwm, MOTOR_POW); 
  digitalWrite(pA, 0); 
  digitalWrite(pB, 1); 
}

void stopMove(){
  analogWrite(pwm, 0); 
  digitalWrite(pA, 0); 
  digitalWrite(pB, 0); 
  delay(25);
}

