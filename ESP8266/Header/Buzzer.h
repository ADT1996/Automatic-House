#ifndef BUZZER_h
#define BUZZER_h

	#include "Utility.h"
	#include "Sensor.h"
	
	const int Buzzer = 13;
	bool buzzerIsOn = false;
	
	void setupPinBuzzer();
	void Alarm();
#endif