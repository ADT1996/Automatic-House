#include "Header/ControlTheDoorOffline.h"

void Task_Keypad(void* parameter) {
  while (true) {
    char key = myKeypad.getKey();

    switch (key) {
      case '\0':
        break;

      case '#': {
          Key_Buff[i] = '\0';
          int lenBuff = strlen(Key_Buff);
          int lenOur = strlen(ourCode);

          if (strcmp(Key_Buff, ourCode) != 0) {
            Door_Stt = 0;
          } else {
            Door_Stt = 1;
          }

          if (Door_Stt == 1 ) {
            count = 3;
            clearLCD();
            setCursorLCD(1,0);
            writeLCD("Mo thanh cong");
            mocua();
            vTaskDelay(5000);
//            if (!lock) /
            dongcua();
            Door_Stt = 0;
          } else {
            count--;
            if (count == 0) {
              Serial.println("Count = 0");
              clearLCD();
              setCursorLCD(2,0);
              writeLCD("Sai mat khau");
              setCursorLCD(2,1);
              writeLCD("Doi 15 giay");
              vTaskDelay(15000);
              count = 3;
            } else {
              clearLCD();
              setCursorLCD(2,0);
              writeLCD("Sai mat khau");
              setCursorLCD(1,1);
              writeLCD("Con ");
              writeLCD(count);
              writeLCD(" lan nhap");
              vTaskDelay(2000);
            }
          }

        }

      case '*': {
          clearLCD();
          Serial.println("Da xoa man hinh");
          memset( Key_Buff, '\0', i);
          i = 0;
          break;
        }

      default: {
          if (i != 32) {
            Key_Buff[i] = key;
            writeLCD('*');
            Serial.println(key);
            i++;
          }
          break;
        }
    }
    vTaskDelay(200);
  }
}
