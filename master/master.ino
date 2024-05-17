#define BLYNK_TEMPLATE_ID "TMPL6Tz9C3sFn"
#define BLYNK_TEMPLATE_NAME "den duong thong minh"
#define BLYNK_AUTH_TOKEN "g5CSLxjOSz-zT8aWh9DwosC-Lw9yUfYL"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//Included SoftwareSerial Library
#include <SoftwareSerial.h>
SoftwareSerial s(3, 1);

char auth[] = BLYNK_AUTH_TOKEN;
// char ssid[] = "BDU-Student";
// char pass[] = "HocHoiHieuHanh";

char ssid[] = "Huu Loc ";
char pass[] = "locdeptraivodich";

int slaveData;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  s.begin(9600);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1) {
  toggleLEDs(param.asInt());
}
BLYNK_WRITE(V2) {
  s.write(param.asInt());
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