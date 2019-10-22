#include <Functions.h>

Functions::Functions(){
  //Step motor pinleri 8,9,10,11
  step=StepperMotor(28,30,32,34);

}

//aldığı iki parametrenin biri telefondan geliyor manuel çalıştırma
//motor kısmını incele
void Functions::sogutmaModu(bool bitki,bool fanMod,bool fanKontrol){
  if(fanMod){//otomatik mod
    fan(bitki);
  }
  else{ // MANUEL MOD
    fan(fanKontrol); //açık ise aç
  }

}

void Functions::fan(bool x){
  step.setStepDuration(1);
  if(x){
    while(x){
        step.step(1000);
    }
    }
    else{
      step.step(0);
    }
  }
