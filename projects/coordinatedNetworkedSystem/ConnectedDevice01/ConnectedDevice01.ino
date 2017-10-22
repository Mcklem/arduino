#include <Wire.h>

void setup() {
  
  Serial.begin(9600);
  Serial.print(F("Initialized "));
  Serial.print(DEVICE_ID);
  Serial.print(" ");
  Serial.print(DEVICE_TYPE);
  Serial.println();

  Wire.begin(DEVICE_ID);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
}

void loop(){
  delay(10);
}

String receivedId = "";
//Receive request id
void receiveEvent(int howMany){
  Serial.print(F("RECEIVED "));
  Serial.print(howMany);
  Serial.print(" ");
  receivedId = "";
  while (Wire.available()> 0) { // loop through all but the last
    receivedId.concat((char)Wire.read()); // receive byte as a character
  }
  Serial.println(receivedId);
}

void requestEvent() {
  Serial.println(F("REQUESTED"));

  String message = "";
  
  int valueA1 = analogRead(receivedId.toInt());
  if(valueA1!=0)Serial.println(valueA1);
  message = valueA1;
  
  message.concat((char)4);//add EOT keeping message integrity
  byte bytes[message.length()];
  message.getBytes(bytes, message.length());
  Wire.write(bytes, sizeof(bytes));
  
}

