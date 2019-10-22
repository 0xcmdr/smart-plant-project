#ifndef PLANT_H
#define PLANT_H

#include <Arduino.h>
class Bitki{

public:
  Bitki();
  Bitki(String ad,double sic,double nem);
  String adi;
  double sicaklik;
  double nemi;

};

#endif
