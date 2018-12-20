#include "Header/Den.h"

void BatDen() {
//  Serial.println("BatDen");
  b = b + 1;
  a = a + digitalRead(Hongngoai);

  if (a < b) {
    String urlString = host + "Home/setOnOffAllDens?";
    HTTPClient http;

    for(int i = 0; i< nLeds; i++) {
      String s = "";
      http.end();
      digitalWrite(Leds[i], HIGH);
//      Serial.print(s + Leds[i] + " on\n");
    }
    String url = urlString + "status=true";
      http.begin(url);
      http.GET();
  }
      DenSang();
}

void DenSang() {
  if (multiwifi.run() == WL_CONNECTED) {
//    Serial.println("DenSang");
    HTTPClient http;
    String url = host + "Home/getDens";
    bool flag = http.begin(url);
    if (flag) {
//      Serial.println("Flag on");
      int httpCode = http.GET();
      //Serial.print("split");
      // String *a = split(http.getString(),'-');
      if (httpCode == 200) {
        String s = http.getString();
        int count;
//        Serial.println(s);
        String* result = split(s, '-', count);
        int min = nLeds < count ? nLeds : count;
        for (int i = 0; i < min; i++) {
          if (result[i].compareTo("On") == 0) {
            digitalWrite(Leds[i], HIGH);
          } else {
            digitalWrite(Leds[i], LOW);
          }
        }
        delete []result;
        a = 0; b = 0;
//        Serial.print(a);  Serial.print(b);
      }
    } else {
//      Serial.println("Flag off");
    }

    http.end();

  }
}

void setLed() {
//  Serial.println("SetLed");
  pinMode(Hongngoai, INPUT);
  
  for(int i = 0; i < nLeds; i++) {
    pinMode(Leds[i], OUTPUT);
  }
}
