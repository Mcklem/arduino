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
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop(){
  delay(100);
}

void requestEvent() {
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root[F("id")] = DEVICE_ID;
  root[F("type")] = DEVICE_TYPE;
  JsonObject& data = root.createNestedObject(F("data"));
  data[F("time")] = millis()/1000;
  String jsonStr;
  root.printTo(jsonStr);
  
  Serial.print("REQUESTED " );
  Serial.println(jsonStr);

  byte bytes[150];
  jsonStr.getBytes(bytes, 150);
  for(int i = 0; i<150;i++){
    Serial.print((char)bytes);
  }
  Serial.println();
  Wire.write(bytes, 150);
}

