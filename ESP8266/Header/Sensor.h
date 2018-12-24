#ifndef SENSOR_h
#define SENSOR_h

	#include "Utility.h"
	#include "Buzzer.h";
	#include <DHT.h>
	
	const int DHTPIN = 2;
	const int DHTTYPE = DHT11;
	DHT dht(DHTPIN, DHTTYPE);
	int h = -1;    //Biến độ ẩm
	int t = -1;    //Biến nhiệt độ
	unsigned long timeold = 0;
	const int Chuyendong = 16;
	

	void ReadTimeWork();
	void beginDHT();
	void DocNhietDo();
	void ChuyenDong();

#endif
