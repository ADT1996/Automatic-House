#include "Header/ControlTheDoorOnline.h"

void beginWiFi() {

  multiwifi.addAP(ssid1, password1);
  multiwifi.addAP(ssid2, password2);
  multiwifi.addAP(ssid3, password3);

  while (multiwifi.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address");
  Serial.println(WiFi.SSID());
}

void Task_getNewPassword(void* parameter) {
  while (true) {
    if (multiwifi.run() == WL_CONNECTED) {
      char* url = "http://newws.somee.com/CuaRaVao/MatKhauCua";
      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
      String sNewPass = http.getString();

      char* oldPass = ourCode;
      char* cNewPass = new char[sNewPass.length() + 1];

      sNewPass.toCharArray(cNewPass, sNewPass.length() + 1);
      ourCode = cNewPass;
      delete []oldPass;
      Serial.println(ourCode);
    }
    vTaskDelay(1000);
  }
}

void Task_Controlbyweb(void* parameter) {
  while (true) {
    if ((multiwifi.run() == WL_CONNECTED)) { //Check the current connection status

      HTTPClient http;

      http.begin("http://newws.somee.com/CuaRaVao/isMoCua"); //Specify the URL
      int httpCode = http.GET();                                        //Make the request

      if (httpCode == 200) { //Check for the returning code
        String res = http.getString();
        http.end(); //Free the resources
        Serial.println(res);
        if (res.compareTo("True") == 0) {
          mocua();
          vTaskDelay(5000);
          dongcua();
        }
      }
      else {
        Serial.println("Error on HTTP request");
      }
    }
//    vTaskDelay(1000);
  }
}