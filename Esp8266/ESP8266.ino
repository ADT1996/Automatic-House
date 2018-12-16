#include "Header/ESP8266.h"

//TaskNhietDo nhietdo_task;
//TaskBaoDong baodong_task;
//TaskChuyenDong chuyendong_task;
//TaskDen den_task;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setLed();       // Khởi động cảm biến
  beginWiFi();
  NPT();
  oldmillis = ((unsigned long long) (millis()/1000)) * 1000;
  Scheduler.start(new TaskNhietDo());
  Scheduler.start(new TaskBaoDong());
  Scheduler.start(new TaskDen());
  Scheduler.start(new TaskChuyenDong());
  Scheduler.start(new TaskRealTime);
  Scheduler.begin();
}

void loop() {}
