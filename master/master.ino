#define BLYNK_TEMPLATE_ID "TMPL6Tz9C3sFn"
#define BLYNK_TEMPLATE_NAME "den duong thong minh"
#define BLYNK_AUTH_TOKEN "g5CSLxjOSz-zT8aWh9DwosC-Lw9yUfYL"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>  //Included SoftwareSerial Library
SoftwareSerial s(3, 1);

char auth[] = BLYNK_AUTH_TOKEN;
// char ssid[] = "BDU-Student";
// char pass[] = "HocHoiHieuHanh";

char ssid[] = "Huu Loc ";
char pass[] = "locdeptraivodich";

/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;

/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;

void setup() {
  // Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  s.begin(9600);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1){
  toggleLEDs(param.asInt());
}

BLYNK_WRITE(V2) {
}

BLYNK_WRITE(V3) {
}

void toggleLEDs(int data) {
  if (data == 1) {
    s.write(HIGH);
  } else {
    s.write(LOW);
  }
}