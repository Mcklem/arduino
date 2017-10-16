#ifndef RotaryEncoder_h
#define RotaryEncoder_h

typedef enum {NONE,CLOCKWISE, COUNTERCLOCKWISE} RotationVariation;

class RotaryEncoder
{
  public:
	  RotaryEncoder(int CLK, int DT);
    RotaryEncoder(int CLK, int DT, int SW);
    RotationVariation getRotationVariation();
	  bool isPressed();
  private:
    int _pinA = 0;
    int _pinB = 0;
	  int _pinSW = 0;
    int _ALastValue = 0;
};

#endif
