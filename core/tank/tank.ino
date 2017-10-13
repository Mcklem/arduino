int leftMotor = 2;
int rightMotor = 3;

void setup() {
  Serial.begin(9600);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("Forward");
  moveForward();
  delay(3000);
  Serial.println("Stop");
  stopMove();
  delay(1000);
}


  


void moveForward(){
  digitalWrite(leftMotor, HIGH); 
  digitalWrite(rightMotor, HIGH); 
}

void moveBackward(){
  digitalWrite(leftMotor, LOW); 
  digitalWrite(rightMotor, LOW); 
}

void stopMove(){
digitalWrite(leftMotor, LOW); 
digitalWrite(rightMotor, LOW); 
delay(25);
}

