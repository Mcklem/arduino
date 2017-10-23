
#define NOISE_VALUE 1

//WE CAN ALSO REDUCE NOISE ATTACHING A 100-200 OHM RESISTOR FROM A0 TO GROUND IN ORDER TO ADJUST RECEIVED VOLTAGE

void setup() {
    Serial.begin(9600);
    analogReference(INTERNAL);
}
  
  void loop() {
  
    int sensorValue = 0;
    
    sensorValue = analogRead(A0);
    if(sensorValue>NOISE_VALUE){
      Serial.print("READ: ");
      Serial.println(sensorValue);
    }
    
    delay(1);
  }
  
