
#include <Thread.h>
#include <StaticThreadController.h>
#include "./RotaryEncoder.h"

int pinA = 3;  // Connected to CLK on KY-040
int pinB = 4;  // Connected to DT on KY-040
int pinSW = 5; // Connected to SW on KY-040
int encoderPositionCount = 1000;

RotaryEncoder rotaryEncoder = RotaryEncoder(pinA, pinB, pinSW);
Thread potenciometerThread = Thread();
Thread ledBlinkThread = Thread();
StaticThreadController<2> threadController (&potenciometerThread, &ledBlinkThread);

unsigned long lastMicros = 0;

void setup() {
  potenciometerThread.onRun(UpdateSensor);
  potenciometerThread.setInterval(0);
  
  ledBlinkThread.onRun(UpdateLed);
  ledBlinkThread.setInterval(0);

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin (9600);
}

void loop() {
  threadController.run();
}

void UpdateLed() {

if(micros()>=lastMicros){
  if(digitalRead(LED_BUILTIN)==HIGH) digitalWrite(LED_BUILTIN, LOW);
  else digitalWrite(LED_BUILTIN, HIGH);
  lastMicros = micros() + encoderPositionCount;
}
  
}

void UpdateSensor() {

  RotationVariation variation = rotaryEncoder.GetRotationVariation();
  if(variation != NONE){
        Serial.print ("Rotated: ");
      if (variation == CLOCKWISE) {
        Serial.println ("clockwise");
        encoderPositionCount = encoderPositionCount + encoderPositionCount*0.1f + 1;
      } else {
        Serial.println("counterclockwise");
        encoderPositionCount = encoderPositionCount - encoderPositionCount*0.1f;
      }
      Serial.print("Encoder Position: ");
      Serial.println(encoderPositionCount);
  }

  if(rotaryEncoder.IsPressed()) Serial.print("Pressed");
}


