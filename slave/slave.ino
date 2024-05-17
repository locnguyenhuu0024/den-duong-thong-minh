// MEGA 2560 slave
#include <Wire.h>

// LED Definations
#define LED1 31
#define LED2 33
#define LED3 35
#define LED4 37
#define LED5 39

// Cam bien hong ngoai
#define HONGNGOAI 52

// Cam bien anh sang
#define ANHSANG A0

/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;

/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;
int gioBatDen = 18;

// Khai báo biến chứa data doc từ nodemcu
int masterData = 0;
int oldMasterTransportedButtonLED = LOW;
int statusLEDs = LOW;

// Bien Hong ngoai
int hongNgoai = LOW;

// Bien Hong ngoai
int anhSang = 0;
int troiToi = 600;

// Điều khiển thủ công
bool autoMode = true;

void setup() {
  Wire.begin();
  /* cài đặt thời gian cho module */
  //setTime(2, 16, 0, 6, 10, 5, 24); // 01:36:00 CN 10-05-2024
  Serial.begin(9600);
  setUpLEDs();
  setUpCamBien();
}

void loop() {
  readDS1307();
  digitalClockDisplay();

  hongNgoai = readHongNgoai();
  anhSang = readAnhSang();
  masterData = Serial.read();

  // Điều khiển bằng button
  if (masterData == 3) {
    Serial.println("Auto mode: ON");
    autoMode = true;
  } else if (masterData == 2) {
    Serial.println("Auto mode: OFF");
    autoMode = false;
  }

  if (autoMode) {
    if (anhSang > troiToi) {
      Serial.println("Trời tối");
      if ((hour >= gioBatDen || hour <= 6) && minute >= 0) {
        statusLEDs = HIGH;
      } else {
        if (hongNgoai == HIGH) {
          Serial.println("Có người");
          statusLEDs = HIGH;
        } else {
          statusLEDs = LOW;
        }
      }

    } else {
      Serial.println("Trời sáng");
      statusLEDs = LOW;
    }
  } else {
    if (masterData == HIGH) {
      statusLEDs = HIGH;
    } else if (masterData == LOW) {
      statusLEDs = LOW;
    }
  }

  triggerLEDs(statusLEDs);
  delay(1000);
}

void setUpLEDs() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void setUpCamBien() {
  pinMode(HONGNGOAI, INPUT);
  pinMode(ANHSANG, INPUT);
}

void triggerLEDs(int status) {
  digitalWrite(LED1, status);
  digitalWrite(LED2, status);
  digitalWrite(LED3, status);
  digitalWrite(LED4, status);
  digitalWrite(LED5, status);
}

int readHongNgoai() {
  return digitalRead(HONGNGOAI) == LOW ? HIGH : LOW;  // có người thì 1, ngược lại là 0
}

int readAnhSang() {
  return analogRead(ANHSANG);  // đo độ sáng
}

void readDS1307() {
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, NumberOfFields);

  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read());
  hour = bcd2dec(Wire.read() & 0x3f);  // chế độ 24h.
  wday = bcd2dec(Wire.read());
  day = bcd2dec(Wire.read());
  month = bcd2dec(Wire.read());
  year = bcd2dec(Wire.read());
  year += 2000;
}
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num) {
  return ((num / 16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num) {
  return ((num / 10 * 16) + (num % 10));
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour);
  printDigits(minute);
  printDigits(second);
  Serial.print(" ");
  Serial.print(day);
  Serial.print(" ");
  Serial.print(month);
  Serial.print(" ");
  Serial.print(year);
  Serial.println();
}

void printDigits(int digits) {
  // các thành phần thời gian được ngăn chách bằng dấu :
  Serial.print(":");

  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr) {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));  // đặt lại pointer
  Wire.write(dec2bcd(sec));
  Wire.write(dec2bcd(min));
  Wire.write(dec2bcd(hr));
  Wire.write(dec2bcd(wd));  // day of week: Sunday = 1, Saturday = 7
  Wire.write(dec2bcd(d));
  Wire.write(dec2bcd(mth));
  Wire.write(dec2bcd(yr));
  Wire.endTransmission();
}