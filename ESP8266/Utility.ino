#include "Header/Utility.h"

Time::Time() {
  Serial.println("Contructor Time()");
  hour = dateTime.hour;
  min = dateTime.minute;
  sec = dateTime.second;
  Serial.print(hour);
  Serial.print("-");
  Serial.print(min);
  Serial.print("-");
  Serial.println(sec);
}

Time::Time(byte Hour, byte Minute, byte Second) {
	sec = Second;
  min = Minute;
  hour = Hour;
  addSecond((byte)0);
}

void Time::addSecond(byte second) {
	sec += second;
	min += sec/60;
	hour += min/60;
	sec%=60;
	min%=60;
	hour%=24;
}

void Time::addSecond(unsigned long long Millisecond) {
  byte sec = Millisecond / 1000;
  addSecond(sec);
}

void Time::SyncRealTime() {
  unsigned long long m = millis();
  unsigned long long Mseccond = (m > oldmillis ? m - oldmillis : m + 4294967296 - oldmillis);
  if(Mseccond >= 1000) {
    oldmillis = ((unsigned long long) (m/1000)) * 1000;
    Mseccond = ((unsigned long long) (Mseccond/1000)) * 1000;
    addSecond(Mseccond);
  }
}

unsigned int Time::getTimeNumber() {
	unsigned int currentNumberTime = hour * 3600 + min * 60 + sec;
	return currentNumberTime;
}

Time* Time::parseTime(String timeString) {
  int count, i = 0;
  String* result = split(timeString,':',count);
  char* temp[count];
  byte hour;
  byte min;
  byte sec;
  
  if(count >= 1) {
    temp[i] =  new char[result[i].length() + 1];
    result[i].toCharArray(temp[i],result[i].length() + 1);
    hour = atoi(temp[i]);
    i++;
  } else {
    hour = 0;
  }
  
  if(count >= 2) {
    temp[i] =  new char[result[i].length() + 1];
    result[i].toCharArray(temp[i],result[i].length() + 1);
    min = atoi(temp[i]);
    i++;
  } else {
    min = 0;
  }

  if(count >= 3) {
    temp[i] =  new char[result[i].length() + 1];
    result[i].toCharArray(temp[i],result[i].length() + 1);
    sec = atoi(temp[i]);
    i++;
  } else {
    sec = 0;
  }
  
  Time* time_t = new Time(hour, min, sec);
  time_t->addSecond((byte) 0);
  
  for(i = 0; i < count; i++) {
    delete []temp[i];
  }
  
  delete []result;
  return time_t;
}

void setupCurrentTime() {
  Serial.println("setupCurrentTime");
  currentTime = new Time();
}

void beginWiFi() {
    Serial.println("beginWiFi");
    WiFi.persistent(false);
    WiFi.disconnect(true);
    multiwifi.addAP(ssid1, password1);
    multiwifi.addAP(ssid2, password2);
    multiwifi.addAP(ssid3, password3);
    while (multiwifi.run() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("WiFi connected");
}

String* split(String str,char a,int& count) {
  int i;
  int index = 0;
  count = 1;
  String *result = NULL;
  
  for(i=0; i<str.length(); i++){
    if(str[i] == a)
      count++;
  }
  
  result = new String[count];
  result[index] = "";
  
  for(i=0; i<str.length();i++) {
    if(str[i]==a){
      index++;
    } else {
      result[index]+=str[i];
    }
  }
  
  return result;
}

void NPT() {
  NTPtime NTPch("ch.pool.ntp.org");   // Server NTP
  do {
    dateTime = NTPch.getNTPtime(7.0, 0);
  } while(!dateTime.valid);
}
