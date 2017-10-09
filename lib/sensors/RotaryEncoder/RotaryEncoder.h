#ifndef RotaryEncoder_h
#define RotaryEncoder_h

typedef enum {NONE,CLOCKWISE, COUNTERCLOCKWISE} RotationVariation;
typedef enum {NONE, PRESSED} StateVariation;

class RotaryEncoder
{
  public:
	RotaryEncoder(int CLK, int DT);
    RotaryEncoder(int CLK, int DT, int SW);
    RotationVariation GetRotationVariation();
	StateVariation GetStateVariation();
  private:
    int _pinA;
    int _pinB;
	int _pinSW;
    int _ALastValue = 0;
};

#endif
