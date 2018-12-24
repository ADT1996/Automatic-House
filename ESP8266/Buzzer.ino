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
      int can = mess.compareTo("On");
      Serial.print(mess);
      Serial.print(' ');
      Serial.println(can);
      if (can == 0) {
        digitalWrite(Buzzer, HIGH);
        buzzerIsOn = true;
        delay(3000);
        digitalWrite(Buzzer, LOW);
        buzzerIsOn = false;
        HTTPClient http1;
        url = host + "Home/setAlarm?status=false";
        http1.begin(url);
        Serial.println(http1.GET());
        http1.end();
      }
    }
    http.end();
  }
//  delay(1000);/
}
