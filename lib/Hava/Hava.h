#ifndef HAVA_H
#define HAVA_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include <AvrI2c_Greiman.h>
#include <LiquidCrystal_I2C_AvrI2C.h>
#include <Wire.h>
#include <virtuabotixRTC.h>

class Hava{
DHT dht2;
virtuabotixRTC myRTC;
public:
LiquidCrystal_I2C_AvrI2C lcd2;
  float dhtSicaklik;
  float dhtNem;
  int suSeviye;
public:
  Hava();
  Hava(int dhtpin);
  float sicakDonder();
  float nemDonder();
  int seviyeDonder();
  void havaToLCD();
  void seviyeToLCD(uint8_t pin);
  String seviyeTespit(uint16_t seviye);
  void RTCtoLCD();
  bool bitkiStabilLCD(double bitSic);
  void saatZamantoLCD();
  void baslangic();
  void manuel(bool x);
  void setRTC(int sn,int dk,int saat,int hgun,int gun,int ay); 
};

#endif
