#ifndef UTILITY
#define UTILITY

	#include <Arduino.h>
	#include <ESP8266HTTPClient.h>
	#include <ESP8266WiFiMulti.h>
	#include <NTPtimeESP.h>

	#define HOSTIFTTT "maker.ifttt.com"
	#define EVENTO "Smart_Home"
	#define IFTTTKEY "mBuHE6gVcIcYgCveyH96y8sgc3LfHmuh6vs5TpE8eKG"
	#define SERVER_PORT "2121"

//	Scheduler Scheduler;
	
	class Time {
		private:
			byte hour;
			byte min;
			byte sec;
		public:
			Time();
			Time(byte,byte,byte);
			void addSecond(byte);
			long getTimeNumber();
			static Time* parseTime(String);
	};
	
	Time* currentTime = NULL;
	Time* timeWorkFrom = NULL;
	Time* timeWorkTo = NULL;
	
	strDateTime dateTime;
	ESP8266WiFiMulti multiwifi;

	const String host = "http://newws.somee.com/";
	
	const char* ssid1 = "BoSu";
	const char* password1 = "DSNW25121996";

	const char* ssid2 = "ADT";
	const char* password2 = "Tuyen@ADT1996";

	const char* ssid3 = "HANHCHINH";
	const char* password3 = "hutech@111111";
	
	void setupCurrentTime();
	void beginWiFi();
	String* split(String,char,int*);
	strDateTime NPT();

#endif
