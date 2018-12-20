#include "Header/Sensor.h"

void beginDHT() {
  dht.begin();
}

void DocNhietDo() {
//  Serial.println("DocNhietDo");
  String s = "";
  int hum = dht.readHumidity();           //Đọc độ ẩm
  int temp = dht.readTemperature();        //Đọc nhiệt độ
//  Serial.println(s + "Nhiet do: " + t + "\nDo am: " + h); //Xuat nhiet do va do am

  if ( (20 <= hum && hum <= 80) || (0 <= temp && temp <= 50) ) {
    if (hum != h || temp != t) {
      t = temp; h = hum;
      String url = host + "Home/setNhietDoDoAm?";
      url = url + "nhietdo=" + t + "&doam=" + h ;
      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
      http.end();
//      Serial.println(httpCode);
    }
  }
  Serial.println();                //Xuống hàng
//  delay(1000);                     //Đợi 1 giây/
}

void ReadTimeWork() {
//  Serial.println("ReadTimeWork");
  if (multiwifi.run() == WL_CONNECTED) {
    HTTPClient http;
    String url = host + "Home/getTimeWork";
    http.begin(url);
    int httpCode = http.GET();
    String timeWork = http.getString();
    http.end();
    int count;
    String* result = split(timeWork, '-', count);

    Time* oldTimeFrom = timeWorkFrom;
    Time* oldTimeTo = timeWorkTo;
    timeWorkFrom = Time::parseTime(result[0]);
    timeWorkTo = Time::parseTime(result[1]);

    if (oldTimeFrom != NULL) {
      delete oldTimeFrom;
    }

    if (oldTimeTo != NULL) {
      delete oldTimeTo;
    }

    delete []result;
//    Serial.println(timeWork);
//    delay(1000);/
  }
}

void ChuyenDong() {
  //if String... bat canh bao
  if (!buzzerIsOn) {
//    Serial.println("alarm is off");
    unsigned int timefrom = timeWorkFrom->getTimeNumber();
    unsigned int timeto = timeWorkTo->getTimeNumber();
    unsigned int currenttime = currentTime->getTimeNumber();

//    Serial.println(timefrom);
    Serial.print(currentTime->hour);
    Serial.print(":");
    Serial.print(currentTime->min);
    Serial.print(":");
    Serial.println(currentTime->sec);
//    Serial.println(timeto);
    
    if (timefrom <= currenttime && currenttime <= timeto) {
      if (digitalRead(Chuyendong) == 1) {
        digitalWrite(Buzzer, LOW);
//        Serial.println("Buzzer on");
      }
      else {
//        Serial.println("Buzzer off");
        digitalWrite(Buzzer, HIGH);
      }
    }
  }
}
