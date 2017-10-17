

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(10);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  Serial.println(readWireMessage());
}

//Receive a message from wire system
String readWireMessage(){
  String message = "";
  while (Wire.available()> 0) { // loop through all but the last
    message.concat((char)Wire.read()); // receive byte as a character
  }
  return message;
}

