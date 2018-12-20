#ifndef SENSOR_h
#define SENSOR_h

	#include "Utility.h"
	#include "Buzzer.h";
	#include <DHT.h>
	
	const int DHTPIN = 2;
	const int DHTTYPE = DHT11;
	DHT dht(DHTPIN, DHTTYPE);
	float h = -1.0f;    //Biến độ ẩm
	float t = -1.0f;    //Biến nhiệt độ

	const int Chuyendong = 16;
	

	void ReadTimeWork();
	void beginDHT();
	void DocNhietDo();
	void ChuyenDong();

#endif