
void setup() {
  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(A0);
  // print out the value you read:
  
  delay(100);
  if(sensorValue>0){
  Serial.println(sensorValue);
  }
}
