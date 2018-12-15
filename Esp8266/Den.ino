#include "Header/Den.h"

void BatDen() {
  b = b + 1;
  a = a + digitalRead(Hongngoai);

  if (a < b) {
    String url = "http://webdemo.somee.com/Home/setDenBatTat?index=";
    HTTPClient http;

    for(int i = 0; i< nLeds; i++) {
      http.begin(url + (i + 1) +"&status=true");
      http.GET();
      digitalWrite(Leds[i], HIGH);
      http.end();
    }
  }
      DenSang();
}

void setLed() {
  pinMode(Hongngoai, INPUT);
  
  for(int i = 0; i < nLeds; i++) {
    pinMode(Leds[i], OUTPUT);
  }
  //  pinMode(Led4, OUTPUT);
//  pinMode(Chuyendong, INPUT);
//  pinMode(Buzzer, OUTPUT);
}
