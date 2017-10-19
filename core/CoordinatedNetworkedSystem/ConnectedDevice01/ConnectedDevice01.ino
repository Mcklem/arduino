#include <ArduinoJson.h>
#include <Wire.h>
#include "./WireControl.h"

#define DEVICE_ID 14
#define DEVICE_TYPE "Clock"

void setup() {
  
  Serial.begin(9600);
  Serial.print("Initialized ");
  Serial.print(DEVICE_ID);
  Serial.print(" ");
  Serial.print(DEVICE_TYPE);
  Serial.println();
  
  Wire.begin(42);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
}

void loop(){
  delay(100);
}

String receivedId = "";
//Receive request id
void receiveEvent(int howMany){
  Serial.print("RECEIVED ");
  Serial.print(howMany);
  Serial.print(" ");
  receivedId = WireControl::readWireMessage();
  Serial.print(receivedId);
  Serial.println();
}

void requestEvent() {
  
  /*StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root[F("id")] = DEVICE_ID;
  root[F("type")] = DEVICE_TYPE;
  JsonObject& data = root.createNestedObject(F("data"));
  data[F("time")] = millis()/1000;*/
  //String jsonStr = "";
  //root.printTo(jsonStr);
  
  Serial.println("REQUESTED");
  String message = receivedId;
  message.concat((char)4);//add EOT keeping message integrity
  byte bytes[message.length()];
  message.getBytes(bytes, message.length());
  Wire.write(bytes, sizeof(bytes));
  
}

