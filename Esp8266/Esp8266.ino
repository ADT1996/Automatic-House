#include<ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <Scheduler.h>
//#include <SerialESP8266wifi.h>
//#include<String.h>
#include <ESP8266HTTPClient.h>
#include <NTPtimeESP.h>
#define DEBUG_ON

#define SERVER_PORT "2121"
//const char* ssid = "842/1/64";
//const char* password = "Tien0909345001123qwe!@#";

strDateTime dateTime;

const char* ssid1 = "BoSu";
const char* password1 = "DSNW25121996";

const char* ssid2 = "ADT";
const char* password2 = "Tuyen@ADT1996";

const char* ssid3 = "HANHCHINH";
const char* password3 = "hutech@111111";

#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "Smart_Home"
#define IFTTTKEY "mBuHE6gVcIcYgCveyH96y8sgc3LfHmuh6vs5TpE8eKG"

ESP8266WiFiMulti multiwifi;

WiFiClientSecure client;
//=====================Nhiet Do=============================
const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
float h;    //Đọc độ ẩm
float t; //Đọc nhiệt độ

void DocNhietDo() {
  h = dht.readHumidity();
  t = dht.readTemperature(); //Xuất nhiệt độ
  
  Serial.print("Nhiet do: ");
  Serial.println(t);
  Serial.print("Do am: ");
  Serial.println(h);               //Xuất độ ẩm

  Serial.println();                //Xuống hàng
  delay(1000);                     //Đợi 1 giây
}
//==========================================================

//==================split===================================
String* split(String str,char a) {
  int i;
  int index = 0;
  int count = 1;
  String *result = NULL;
  
  for(i=0; i<str.length(); i++){
    if(str[i] == a)
      count++;
  }
  
  result = new String[count];
  result[index] = "";
  
  for(i=0; i<str.length();i++) {
    if(str[i]==a){
      index++;
    } else {
      result[index]+=str[i];
    }
  }
  
  return result;
}
//==========================================================



bool NPT() {
  NTPtime NTPch("ch.pool.ntp.org");   // Server NTP
  dateTime = NTPch.getNTPtime(7.0, 0);

  // Kiem tra dateTime.valid truoc khi dua ra gia tri thoi gian
  if (dateTime.valid) {
    return true;
//    NTPch.printDateTime(dateTime);
//
//    byte actualHour = dateTime.hour;      // Gio
//    byte actualMinute = dateTime.minute;  // Phut
//    byte actualsecond = dateTime.second;  // Giay
//    int actualyear = dateTime.year;       // Nam
//    byte actualMonth = dateTime.month;    // Thang
//    byte actualday = dateTime.day;        // Ngay
//    byte actualdayofWeek = dateTime.dayofWeek; // Ngay trong tuan
  }
  return false;
}

//=====================Hong ngoai===========================
const int Hongngoai = 5;
const int Led1 = 14;
const int Led2 = 0;
const int Led3 = 12;
//const int Led4 = 4;
int a = 0;
int b = 0;
void DenSang() {
  if (multiwifi.run() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://webdemo.somee.com/Home/getDens";
    http.begin(url);
    http.GET();
    //Serial.print("split");
    // String *a = split(http.getString(),'-');
    String s = http.getString();
    http.end();
    if (s.compareTo("On-Off-Off") == 0)
    { a = 0; b = 0;
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
    }


    if (s.compareTo("Off-On-Off") == 0)
    { a = 0; b = 0;
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, LOW);
    }


    if (s.compareTo("Off-Off-On") == 0) {

      a = 0; b = 0;
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, HIGH);
    }


    if (s.compareTo("Off-On-On") == 0) {
      a = 0; b = 0;
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
    }


    if (s.compareTo("On-Off-On") == 0) {

      a = 0; b = 0;
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, HIGH);
    }

    if (s.compareTo("On-On-Off") == 0) {
      a = 0; b = 0;
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, LOW);
    }


    if (s.compareTo("On-On-On") == 0) {
      a = 0; b = 0;
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
    }

    if (s.compareTo("Off-Off-Off") == 0) {
      a = 0; b = 0;
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
    }
    Serial.print(a);  Serial.print(b);
  }
}
void BatDen() {
  b = b + 1;
  a = a + digitalRead(Hongngoai);

  if (a < b) {
    HTTPClient http;
  http.begin("http://webdemo.somee.com/Home/setDenBatTat?index=1&status=true");
      http.GET();
       digitalWrite(Led1, HIGH);
      http.end();
      http.begin("http://webdemo.somee.com/Home/setDenBatTat?index=2&status=true");
      http.GET();
      digitalWrite(Led2, HIGH);
      http.end();
      http.begin("http://webdemo.somee.com/Home/setDenBatTat?index=3&status=true");
      http.GET();
      digitalWrite(Led3, HIGH);
      http.end();
  }
  
  
      DenSang();


}
//==========================================================

//=====================Chuyen dong==========================
const int Chuyendong = 16;
const int Buzzer = 13;
void ChuyenDong() {
  //if String... bat canh bao

  Serial.println(digitalRead(Chuyendong));
  if (digitalRead(Chuyendong) == 1) {
    digitalWrite(Buzzer, LOW);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(500);
  }
  else {
    digitalWrite(Buzzer, HIGH);
  }
}
//==========================================================



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.persistent(false);
  WiFi.disconnect(true);
  multiwifi.addAP(ssid1, password1);
  multiwifi.addAP(ssid2, password2);
  multiwifi.addAP(ssid3, password3);
  while (multiwifi.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  dht.begin();         // Khởi động cảm biến
  delay(2000);
  /*Sim800l.begin();
    text="Testing Sms";  //text for the message.
    number="0357760866"; //change to a valid number.
    error=Sim800l.sendSms(number,text);*/
  // OR
  //Sim800l.sendSms("+540111111111","the text go here")
  pinMode(Hongngoai, INPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  //  pinMode(Led4, OUTPUT);
  pinMode(Chuyendong, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(DHTPIN, OUTPUT);


  /*if (client.connected())
    { client.stop();
    }
    client.flush();
    if (client.connect(HOSTIFTTT, 443)) {
    Serial.println("Ifttt Connected");

    //String toSend = "https://maker.ifttt.com/trigger/ESP_DHT11/with/key/fSqSQdQlkoV585c9yaCpJbHFYldBc07B4cccF4L3OvA";
    String toSend =  "GET /trigger/";
    toSend += EVENTO;
    toSend += "/with/key";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += t;
    toSend += "?value2=";
    toSend += h;
    Serial.print(toSend);
    toSend += "HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close \r\n\r\n";
    //client.print(toSend);
    }

    client.flush();
    client.stop();
    delay(500);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  DocNhietDo();
  BatDen();
  ChuyenDong();

  bool NTP = NPT();
  /// delay(2000);


}
