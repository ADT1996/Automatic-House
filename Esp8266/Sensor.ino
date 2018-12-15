#include "Header/Sensor.h"

void setupPinBuzzer() {
  pinMode(Buzzer,OUTPUT);
  pinMode(Chuyendong,INPUT);
}

void beginDHT() {
  dht.begin();
}

void DocNhietDo() {
  int hum = dht.readHumidity();           //Đọc độ ẩm
  int temp = dht.readTemperature();        //Đọc nhiệt độ
  Serial.print("Nhiet do: ");
  Serial.println(t);                //Xuất nhiệt độ
  Serial.print("Do am: ");
  Serial.println(h);               //Xuất độ ẩm

  if ( (20 <= hum && hum <= 80) || (0 <= temp && temp <= 50) ) {
    if (hum != h || temp != t) {
      t = temp; h = hum;
      String func = "Home/setNhietDoDoAm?";
      func = host + func + "nhietdo=" + t + "&doam=" + h ;
      char URI[func.length() + 1];
      func.toCharArray(URI,func.length() + 1);
      HTTPClient http;
      http.begin(URI);
      int httpCode = http.GET();
      http.end();
      Serial.println(httpCode);
    }
  }
  Serial.println();                //Xuống hàng
  delay(1000);                     //Đợi 1 giây
}

void ReadTimeWork() {
  if(multiwifi.run() == WL_CONNECTED) {
    HTTPClient http;
    String func = host + "Home/getTimeWork";
    char URI[func.length() + 1];
    func.toCharArray(URI,func.length() + 1);
    http.begin(URI);
    int httpCode = http.GET();
    String timeWork = http.getString();
    http.end();
    int count;
    String* result = split(timeWork,'-',&count);

    Time* oldTimeFrom = timeWorkFrom;
    Time* oldTimeTo = timeWorkTo;
    timeWorkFrom = Time::parseTime(result[0]);
    timeWorkTo = Time::parseTime(result[1]);

    if(oldTimeFrom != NULL) {
      delete oldTimeFrom;
    }

    if(oldTimeTo != NULL) {
      delete oldTimeTo;
    }
    
    delete []result;
  }
}

void ChuyenDong() {
  //if String... bat canh bao
  
  Serial.println(digitalRead(Chuyendong));
  if (digitalRead(Chuyendong) == 1) {
    digitalWrite(Buzzer, LOW);
    delay(500);
  }
  else {
    digitalWrite(Buzzer, HIGH);
  }
}
