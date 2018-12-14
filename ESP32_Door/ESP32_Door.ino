#include "Header/TheDoor.h"

TaskHandle_t Task1, Task2, Task3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  setDoor();
  initLCD();
  writeLCD("Hello");
  clearLCD();
  
  xTaskCreatePinnedToCore(
    Task_Keypad, /* Task function. */
    "Task_Keypad", /* String with name of task. */
    10000, /* Stack size in words. */
    NULL, /* Parameter passed as input of the task */
    1, /* Priority of the task. */
    &Task1, /* Task handle. */
    1); /* Core. */
    
  beginWiFi();
  
  xTaskCreatePinnedToCore(
    Task_Controlbyweb, /* Task function. */
    "Task_Controlbyweb", /* String with name of task. */
    10000, /* Stack size in words. */
    NULL, /* Parameter passed as input of the task */
    2, /* Priority of the task. */
    &Task2, /* Task handle. */
    0); /* Core. */

  

  xTaskCreatePinnedToCore(
    Task_getNewPassword,
    "Task_getNewPassword",
    10000,
    NULL,
    1,
    &Task3,
    1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
