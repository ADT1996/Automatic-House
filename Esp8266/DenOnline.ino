#include "Header/DenOnline.h"

void DenSang() {
  if (multiwifi.run() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://webdemo.somee.com/Home/getDens";
    http.begin(url);
    http.GET();
    //Serial.print("split");
    // String *a = split(http.getString(),'-');
    String s = http.getString();
    http.end();
    int count;
    String* result = split(s,'-',&count);
    int min = nLeds < count ? nLeds : count;
    for(int i = 0; i < min; i++) {
      if (result[i].compareTo("On") == 0) {
        digitalWrite(Leds[i], HIGH);
      } else {
        digitalWrite(Leds[i], LOW);
      }
    }
    delete []result;
    a = 0; b = 0;
    Serial.print(a);  Serial.print(b);
  }
}
