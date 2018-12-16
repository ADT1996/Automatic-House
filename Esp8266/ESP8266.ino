#include "Header/ESP8266.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setLed();       // Khởi động cảm biến
  beginWiFi();
  Scheduler.start(&nhietdo_task);
  Scheduler.start(&baodong_task);
  Scheduler.start(&chuyendong_task);
  Scheduler.start(&den_task);
  Scheduler.begin();
}

void loop() {}
