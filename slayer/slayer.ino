// MEGA 2560 slave
#include <Wire.h> 

// ESP8266 Define variables
#define CMD_SEND_BEGIN  "AT+CIPSEND=0"
#define CMD_SEND_END    "AT+CIPCLOSE=0"

#define STDIO_PROTOCOL_HTTP     80
#define STDIO_PROTOCOL_HTTPS    443
#define STDIO_PROTOCOL_FTP      21
#define STDIO_PROTOCOL_CURRENT  STDIO_PROTOCOL_HTTP

#define STDIO_CHAR_CR     0x0D
#define STDIO_CHAR_LF     0x0A

#define STDIO_STRING_EMPTY  ""

#define STDIO_DELAY_SEED  1000
#define STDIO_DELAY_1X    (1*STDIO_DELAY_SEED)
#define STDIO_DELAY_2X    (2*STDIO_DELAY_SEED)
#define STDIO_DELAY_3X    (3*STDIO_DELAY_SEED)
#define STDIO_DELAY_4X    (4*STDIO_DELAY_SEED)
#define STDIO_DELAY_5X    (5*STDIO_DELAY_SEED)

bool hasRequest = false;
/////////////////////////////////////

// LED Definations
#define LED1 31
#define LED2 33
#define LED3 35
#define LED4 37
#define LED5 39
 
/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;
 
/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;
 
void setup()
{
  Wire.begin();
  /* cài đặt thời gian cho module */
  //setTime(2, 16, 0, 6, 10, 5, 24); // 01:36:00 CN 10-05-2024
  Serial.begin(9600);
}
 
void loop()
{  
  /* Đọc dữ liệu của DS1307 */
  readDS1307();
  /* Hiển thị thời gian ra Serial monitor */
  digitalClockDisplay();
  delay(1000);
}
 
void readDS1307()
{
        Wire.beginTransmission(DS1307);
        Wire.write((byte)0x00);
        Wire.endTransmission();
        Wire.requestFrom(DS1307, NumberOfFields);
        
        second = bcd2dec(Wire.read() & 0x7f);
        minute = bcd2dec(Wire.read() );
        hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
        wday   = bcd2dec(Wire.read() );
        day    = bcd2dec(Wire.read() );
        month  = bcd2dec(Wire.read() );
        year   = bcd2dec(Wire.read() );
        year += 2000;    
}
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}
 
void digitalClockDisplay(){
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
 
void printDigits(int digits){
    // các thành phần thời gian được ngăn chách bằng dấu :
    Serial.print(":");
        
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
 
/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(min));
        Wire.write(dec2bcd(hr));
        Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
        Wire.write(dec2bcd(d)); 
        Wire.write(dec2bcd(mth));
        Wire.write(dec2bcd(yr));
        Wire.endTransmission();
}