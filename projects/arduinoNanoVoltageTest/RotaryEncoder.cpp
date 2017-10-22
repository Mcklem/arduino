#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int CLK, int DT)
{
    _pinA = CLK;
    _pinB = DT;
	  pinMode (_pinA, INPUT);
    pinMode (_pinB, INPUT);
    /* Read Pin A
      Whatever state it's in will reflect the last position
    */
    _ALastValue = digitalRead(_pinA);
}

RotaryEncoder::RotaryEncoder(int CLK, int DT, int SW)
{
    _pinA = CLK;
    _pinB = DT;
	  _pinSW = SW;
    pinMode (_pinA, INPUT);
    pinMode (_pinB, INPUT);
	  pinMode (_pinSW, INPUT);
    _ALastValue = digitalRead(_pinA);
}

bool RotaryEncoder::isPressed(){
  return digitalRead(_pinSW)==LOW;
}

RotationVariation RotaryEncoder::getRotationVariation()
{
  RotationVariation variation = NONE;
  int aValue = digitalRead(_pinA);

  if (aValue != _ALastValue) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(_pinB) != aValue) {  // Means pin A Changed first - We're Rotating Clockwise
      variation = COUNTERCLOCKWISE;
    } else {// Otherwise B changed first and we're moving CCW
      variation = CLOCKWISE;
    }
  }
  _ALastValue = aValue;
  return variation;
}
