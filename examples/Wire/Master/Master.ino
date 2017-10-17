
#include <Wire.h>
#include "./WireControl.h"

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.onRequest(request)
}

int x = 0;

void loop() {

  String string = "this is a test";
  string.concat(x);
  WireControl::sendWireMessage(8, string);
  x++;
  delay(100);
}

void request(){
  Serial.println("REQUEST");
}


