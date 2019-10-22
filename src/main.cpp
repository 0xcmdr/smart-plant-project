#include <Arduino.h> //KLASİK ARDUINO KÜTÜPHANESİ
#include <Hava.h> //METHODLARIMIZIN BULUNDUĞU,YAZDIĞIMZI SINIF
#include <Plant.h>//BITKI BİLGİLERİNİN TUTULDUĞU SINIF
#include <StepperMotor.h> //HARİCİ STEPMOTOR KÜTÜPHANESİ
#include <CreateTimer.h> //HARİCİ ZAMANLAYICI KÜTÜPHANESİ
void fan(bool x);
void sogutmaModu(bool bitki,bool fanMod,bool fanKontrol);
Hava hava1; //Fonksiyonlarımızı çalıştırmamızı sağlayacak nesnemiz
Bitki bitki1; //Bitki bilgilerini tutacağımız nesnemiz
bool fanKontrol; //Fanın açık kapalı olduğunu kontrol eder
bool fanMod; //Otomatik ve Manuel modu ifade eder
bool bitkiFan;  //Otomatik modda fanın durumunu kontrol eder
StepperMotor step; //motoru çalıştırmak için motor nesnemiz
CreateTimer MyTimer; //Zamanlayıcı nesnemiz
CreateTimer My2ndTimer;
CreateTimer My3rdTimer;
CreateTimer MyTimer4;

void setup() {
Serial.begin(115200);
Serial1.begin(9600);
hava1=Hava(8);
fanKontrol=false;
fanMod=true;//TRUE= OTOMATİK
bitkiFan=false;
step=StepperMotor(2,3,4,5);
hava1.baslangic();
MyTimer.Start(10000UL);

}

void loop() {
  while(!(Serial1.available())){
    if(!(bitki1.adi=="Bitki 1")){
      if(!fanMod){ // FAN OTOMATİK MODDA DEĞİLSE
      hava1.manuel(fanKontrol);
      sogutmaModu(false,fanMod,fanKontrol);//MANUEL ÇALIŞTIR
    }
    else{ //FAN OTOMATİK MODDA
      if(MyTimer.Once()){
      hava1.havaToLCD(); //HAVA BİLGİLERİNİ LCD YE YAZDIR
      My2ndTimer.Start(8000UL);
      }

      if(My2ndTimer.Once()){
      hava1.saatZamantoLCD(); //RTC DEN ZAMANI AL LCD YE YAZDIR
      My3rdTimer.Start(8000UL);
        }

      if(My3rdTimer.Once()){
      hava1.seviyeToLCD(A0); // SU SEVİYESİNİ LCD YE YAZDIR
      MyTimer4.Start(8000UL);
      }

      if(MyTimer4.Once()){
      bitkiFan=hava1.bitkiStabilLCD(bitki1.sicaklik);
      sogutmaModu(bitkiFan,fanMod,fanKontrol); //OTOMATİK MODDA FANI ÇALIŞTIR
      MyTimer.Start(2000UL);
      }
    }


    }

  }
  //TELEFONDAN VERİ GELİNCE ÇALIŞACAK KISIM
    String readString;
    while(Serial1.available()){
    delay(3);
    char c = Serial1.read();
    readString+=c;
    }
    //Telefondan veriyi al ve bitkiye yolla
    if(readString.startsWith("bOl")){
      int in1,in2,in3;
      String parca[3];
      in1=readString.indexOf("*");
      in2=readString.indexOf("-");
      in3=readString.indexOf(",");
      parca[0]=readString.substring(in1+1,in2);
      parca[1]=readString.substring(in2+1,in3);
      parca[2]=readString.substring(in3+1);
      Serial.println(parca[0]+parca[1]+parca[2]);
      bitki1=Bitki(parca[0],parca[1].toDouble(),parca[2].toDouble());
    }

  //SENSOR BİLGİLERİNİ GÖNDER
    if(readString=="bAl"){
    Serial1.write(0x0A);
    Serial1.print(hava1.sicakDonder());
    Serial1.write(0x0D);
    delay(50);
    Serial1.write(0x0A);
    Serial1.print(hava1.nemDonder());
    Serial1.write(0x0D);
    }

    //PERVANE DURDURMA VE ÇALIŞTIRMA
    if(readString=="fOn"){
      fanKontrol=true;
      Serial.println("FAN AÇIK");
    }
    if(readString=="fOff"){
      fanKontrol=false;
      Serial.println("FAN KAPALI");
    }
    if(readString=="oto"){ // FAN MODU OTOMATİK
      fanMod=true;
      Serial.println("FAN OTOMATİK");
    }
    if(readString=="manu"){
      fanMod=false;
      Serial.println("FAN MANUEL");
    }
    //SAATİ OLUŞTUR
    if(readString.startsWith("rtc")){
      int in1,in2,in3,in4,in5,in6;
      String parca[6];
      Serial.println("CMD");
      in1=readString.indexOf("*");
      in2=readString.indexOf("-");
      in3=readString.indexOf(",");
      in4=readString.indexOf(".");
      in5=readString.indexOf("+");
      in6=readString.indexOf("/");
      parca[0]=readString.substring(in1+1,in2);
      parca[1]=readString.substring(in2+1,in3);
      parca[2]=readString.substring(in3+1,in4);
      parca[3]=readString.substring(in4+1,in5);
      parca[4]=readString.substring(in5+1,in6);
      parca[5]=readString.substring(in6+1);
      Serial.println("A:"+parca[0]+"B:"+parca[1]+"C:"+parca[2]+"D:"+parca[3]+"E:"+parca[4]+"F:"+parca[5]);
      hava1.setRTC(parca[0].toInt(), parca[1].toInt(), parca[2].toInt(), parca[3].toInt(), parca[4].toInt(),parca[5].toInt());
    }

}

//Fanı açıp kapatan fonksiyonumuz
void fan(bool x){
  step.setStepDuration(1);
  if(x){
    for(int i=0;((!Serial1.available() && x)&&i<18)&&bitki1.adi!="Bitki1";i++){
        step.step(1000);
    }
    }
    else{
      step.step(0);
    }
  }

  //FANIN MODUNU DEĞİŞTİRMEMİZİ SAĞLAYAN FONKSİYONUMUZ
void sogutmaModu(bool bitki,bool fanMod,bool fanKontrol){
  if(fanMod){//otomatik mod
    fan(bitki);
  }
  else{ // MANUEL MOD
    fan(fanKontrol); //açık ise aç
  }

}
