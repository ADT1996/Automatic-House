#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "TheDoor.h"

const char* ssid1 = "BoSu";
const char* password1 = "DSNW25121996";

const char* ssid2 = "ADT";
const char* password2 = "Tuyen@ADT1996";

const char* ssid3 = "HANHCHINH";
const char* password3 = "hutech@111111";

WiFiMulti multiwifi;

void beginWiFi();
void Task_Controlbyweb(void*);
void Task_getNewPassword(void*);
