#include "Header/Buzzer.h"

void setupPinBuzzer() {
//  Serial.println("setupPinBuzzer");
  pinMode(Buzzer, OUTPUT);
  pinMode(Chuyendong, INPUT);
}

void Alarm() {
  if (multiwifi.run() == WL_CONNECTED) {
    String url = host + "Home/getAlarm";
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String mess = http.getString();
      if (mess.compareTo("On") == 0) {
        digitalWrite(Buzzer, LOW);
        buzzerIsOn = true;
        delay(3000);
        digitalWrite(Buzzer, HIGH);
        buzzerIsOn = false;
        HTTPClient http1;
        url = host + "Home/setAlarm?status=false";
        http1.begin(url);
        http1.GET();
        http1.end();
      }
    }
    http.end();
  }
  delay(1000);
}
