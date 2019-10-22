#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <StepperMotor.h>

class Functions{

StepperMotor step;
public:
  Functions();
  void sogutmaModu(bool bitki,bool fanMod,bool fanKontrol); // pervane motorunu aktif etmek için
  void fan(bool x);

};

#endif
