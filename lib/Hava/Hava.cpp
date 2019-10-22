#include <Hava.h>

Hava::Hava(){
}

//CONSTRUCTOR
Hava::Hava(int dhtpin){
  //DHT SENSORUNU TANIMLA
dht2=DHT(dhtpin,DHT11);
dht2.begin();
//LCD TANIMLA
lcd2=LiquidCrystal_I2C_AvrI2C (0x3F,16,2);
//RTC SAAT MODU CL,DAT,RST
myRTC=virtuabotixRTC(48,50,52);
//Elle tarih girildi
}

//DHT'DEN SICAKLIK DONDERIR
float Hava::sicakDonder(){
  return (dhtSicaklik=dht2.readTemperature(false));
}

//DHT DEN NEM DONDERIR
float Hava::nemDonder(){
return (dhtNem=dht2.readHumidity());
}

//SICAKLIK VE NEMI DHT'DEN OKUYUP LCDYE YAZDIRIR
void Hava::havaToLCD(){
  lcd2.begin();
  dhtSicaklik=dht2.readTemperature(false);
  dhtNem=dht2.readHumidity();
  lcd2.setCursor(0,0);
  lcd2.print("Sensor Okunuyor...");
  delay(1000);
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Sicaklik : ");lcd2.println(dhtSicaklik);
  lcd2.setCursor(0,1);
  lcd2.print("Nem : ");lcd2.print(dhtNem);
  delay(2000);
}

//SU SEVİYESİNİ LCD YE YAZDIRIR
void Hava::seviyeToLCD(uint8_t pin){
//Su seviyesini yazdır
  lcd2.begin();
  suSeviye=analogRead(pin);
  String metin=seviyeTespit(suSeviye);
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("Su Seviyesi : ");lcd2.print(suSeviye);
  lcd2.setCursor(0,1);
  lcd2.print(metin);

  }

  //SU SEVİYESİNİ BELİRLER
 String Hava::seviyeTespit(uint16_t seviye){
  String sonuc="Su Seviyesi Belirlenemedi!";
  if(seviye <150)
    sonuc="Seviye Dusuk!";
  else if(seviye>350)
    sonuc="Seviye Yuksek!";
  else
    sonuc="Seviye Normal";
  return sonuc;
  delay(3000);
  }

  //Bundan dönecek değer soğutmaModu fonksiyonunda kullanılacak
  bool Hava::bitkiStabilLCD(double bitSic){
    lcd2.begin();
    bool kontrol;
    if(bitSic+3 < sicakDonder() || bitSic-3 > sicakDonder()){
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Stabil Degil!");
      delay(2000);
      lcd2.setCursor(0,1);
      lcd2.print("Pervane Acik.");
      delay(1000);
      kontrol=true;
    }
    else{
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Sartlar : Stabil");
      delay(2000);
      lcd2.setCursor(0,1);
      lcd2.print("Pervane Kapali.");
      delay(1000);
      kontrol=false;
    }
    return kontrol;
    }
    //RTC DEN DONEN VERIYI EKRANA YAZDIRACAK
    void Hava::saatZamantoLCD(){
      myRTC.updateTime();
      lcd2.begin();
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Tarih:");
      lcd2.print(myRTC.dayofmonth);
      lcd2.print("/");
      lcd2.print(myRTC.month);
      lcd2.print("/");
      lcd2.print(myRTC.year);
      lcd2.print(" ");
      lcd2.setCursor(0,1);
      lcd2.print("Saat:");
      lcd2.print(myRTC.hours);
      lcd2.print(":");
      lcd2.print(myRTC.minutes);
      lcd2.print(":");
      lcd2.print(myRTC.seconds);
      lcd2.print(" ");
      delay(5000);
      lcd2.clear();
      lcd2.setCursor(0,0);
     if(myRTC.hours > 18){
        lcd2.print("Hava Karanlik!");
      }
      else{
        lcd2.print("Hava Aydinlik!");
      }
    }
    void Hava::baslangic(){
      lcd2.begin();
      lcd2.setCursor(0,0);
      lcd2.print("Baslatiliyor...");
      delay(2000);
      lcd2.setCursor(0,1);
      lcd2.print("Lutfen Bitki Seciniz...");
    }
    void Hava::manuel(bool x){
      lcd2.begin();
      lcd2.setCursor(0,0);
      lcd2.print("MANUEL MOD");
      delay(1000);
      if(x){
        lcd2.setCursor(0,1);
        lcd2.print("Fan Acik!");
      }
      else{
        lcd2.setCursor(0,1);
        lcd2.print("Fan Kapali!");
      }
    }

    void Hava::setRTC(int sn,int dk,int saat,int hgun,int gun,int ay){
      myRTC.setDS1302Time(sn, dk, saat, hgun, gun, ay, 2018);
    }
