#ifndef THEDOOR_h
#define THEDOOR_h

//#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define LED_BUILTIN 2

LiquidCrystal_I2C lcd(0x27,16,2);

int count = 3;
bool door = false;
bool lock = false;

const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 33;
const int IN4 = 32;
int Steps = 0;

bool Direction = true;

unsigned long last_time;
unsigned long currentMillis ;

int steps_left = 1150;
long time1;
char* ourCode = new char[5] {'1','2','3','4','\0'};

void initLCD();
void clearLCD();
void setCursorLCD(int,int);
void writeLCD(const char*);
void writeLCD(const char);
void setDoor();
void mocua();
void dongcua();

#endif
