//#include <Stepper.h>
#include "Header/TheDoor.h"

void SetDirection();
void motor();
void stepper(int);

void setDoor() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void mocua() {
  if (!door) {
    digitalWrite(LED_BUILTIN, HIGH);
    motor();
    door = !door;
    Direction = !Direction;
    steps_left = 1150;
  }
}

void dongcua() {
  if (door) {
    digitalWrite(LED_BUILTIN, LOW);
    motor();
    door = !door;
    Direction = !Direction;
    steps_left = 1150;
  }
}
//====================================================================================================

void motor() {
  while (steps_left > 0) {
    currentMillis = micros();
    if (currentMillis - last_time >= 1000) {
      stepper(1);
      time1 = time1 + micros() - last_time;
      last_time = micros();
      steps_left--;
    }
  }
}

//=============================================
//motor
void stepper(int xw) {
  for (int x = 0; x < xw; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break;
      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
    SetDirection();
  }
}

void SetDirection() {
  if (Direction == 1)
    Steps++;
  if (Direction == 0)
    Steps--;
  if (Steps > 7)
    Steps = 0;
  if (Steps < 0)
    Steps = 7;
}

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.home();
}

void clearLCD() {
  lcd.clear();
  lcd.home();
}

void setCursorLCD(int x,int y) {
  lcd.setCursor(x,y);
}

void writeLCD(const char* text) {
  lcd.print(text);
}

void writeLCD(const char chr) {
  lcd.print(chr);
}
