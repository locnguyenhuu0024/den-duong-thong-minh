#define BLYNK_TEMPLATE_ID "TMPL6Tz9C3sFn"
#define BLYNK_TEMPLATE_NAME "den duong thong minh"
#define BLYNK_AUTH_TOKEN "g5CSLxjOSz-zT8aWh9DwosC-Lw9yUfYL"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h> //Included SoftwareSerial Library

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Huu Loc ";
char pass[] = "locdeptraivodich";
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
 }
  
void loop()
{ 
  Blynk.run(); 
}
BLYNK_WRITE(V1)
{
   digitalWrite(LED1, param.asInt());
   digitalWrite(LED2, param.asInt());
   digitalWrite(LED3, param.asInt());
   digitalWrite(LED4, param.asInt());
   digitalWrite(LED5, param.asInt());
}
BLYNK_WRITE(V2)
{
}
BLYNK_WRITE(V3)
{
}