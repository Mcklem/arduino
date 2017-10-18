#include "Arduino.h"
#include "Wire.h"
#include "WireControl.h"

#define sendWireMessage(device,message) WireControl::sendWireMessage(device, message)

//Sends a message to device through wire system
void WireControl::sendWireMessage(int device, String message)
{
  message.concat((char)4);//add EOT keeping message integrity
  Wire.beginTransmission(device);
  byte bytes[message.length()];
  message.getBytes(bytes, message.length());
  Wire.write(bytes, sizeof(bytes));
  Wire.endTransmission();
}

//Receive a message from wire system
String WireControl::readWireMessage()
{
  String message = "";
  while (Wire.available()> 0) { // loop through all but the last
    message.concat((char)Wire.read()); // receive byte as a character
  }
  return message;
}
