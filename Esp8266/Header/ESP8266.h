#ifndef ESP8266_h
#define ESP8266_h

	#include "Utility.h"
	#include "Sensor.h"
	#include "Den.h"
	#include <Scheduler.h>


	class TaskNhietDo : public Task {
		protected:
			void setup() {
				beginDHT();
			}

			void loop () {
				DocNhietDo();
			}
	};

	class TaskDen : public Task {
		protected:
			void setup() {
				setLed();
			}

			void loop () {
				BatDen();
			}
	};
	
	class TaskBaoDong : public Task {
		protected:
			void setup() {
				setupCurrentTime();
			}

			void loop () {
				ReadTimeWork();
			}
	};

	class TaskChuyenDong : public Task {
		protected:
			void setup() {
				setupPinBuzzer();
			}

			void loop () {
				ChuyenDong();
			}
	};

	TaskNhietDo nhietdo_task;
	TaskBaoDong baodong_task;
	TaskChuyenDong chuyendong_task;
	TaskDen den_task;

#endif