#include <string.h>
#include <Keypad.h>
#include "TheDoor.h"

const byte n_rows = 4;
const byte n_cols = 4;
char keys[n_rows][n_cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char Key_Buff[33];
int i = 0, Door_Stt = 0;

byte rowPins[n_cols] = {14, 27, 26, 25};
byte colPins[n_rows] = {5, 18, 19, 23};
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols);

void Task_Keypad(void*);
