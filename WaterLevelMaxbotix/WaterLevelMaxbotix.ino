// KONFIGURASI INTERNET GPRS
#define GPRS_APN "axis"
#define GPRS_USER "axis"
#define GPRS_PASS "123456"

//KONFIGURASI THINGSPEAK
String SECRET_WRITE_APIKEY = "MN3RFZ7MK4HNUPD7";   // ganti dengan channel write API Key

//KONFIGURASI BATAS AIR
#define batas 2000

#include "SdFat.h"
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

//REGISTER PIN
#define oled      0x3c
#define ads_addr    0x48
#define rtc_addr    0x68
#define panjang     128
#define lebar           64
#define pinTekanan       0
#define SCKpin          52
#define MISOpin         50
#define MOSIpin         51
#define SSpin           53
#define buzzer 26

//OLED
#define OLED_RESET 0
Adafruit_SSD1306 display(panjang, lebar, &Wire, OLED_RESET);
int16_t posx;
int16_t posy;
uint16_t w, h;

//RTC DS3231
RTC_DS3231 rtc;
DateTime nows;

//SD CARD
SdFat SD;
File file;
String filename;

//GLOBAL VARIABLE
char str[13];
char sdcard[200];
char g;
byte a, b, c, interval, burst;
byte bulan, hari, jam, menit, detik;
int i, kode, tahun;
unsigned int reads = 0; //pressure
unsigned long start;
unsigned long tinggiAir;
String y, network, APN, operators, result;

void setup() {
  Serial.begin(9600);  // Serial USB
  Serial.println(F("\r\n- WATER LEVEL MONITORING SYSTEM PDAM 2020"));

  Serial.println("\r\n- INISIALISASI -");
  inisialisasi();
  delay(4000);

  Serial.println("\r\n- CEK REAL TIME CLOCK -");
  rtcinit();
  delay(1000);

  Serial.println("\r\n- CEK SD CARD -");
  sdInit();
  delay(1000);

  Serial.println("\r\n- TUNGGU GSM -");
  tungguGSM();
  delay(2000);

  Serial.println("\r\n- CEK MODUL GSM -");
  initGSM();
  delay(2000);

  Serial.println("\r\n- CEK OPERATOR PROVIDER -");
  cekOperator();
  delay(3000);

  Serial.println("\r\n- CEK KEKUATAN SINYAL -");
  cekSinyal();
  delay(3000);

  display.clearDisplay();
  displaydate();

  //display menu parameter
  tampilanAwal();

}

void loop() {
  Serial.println("\r\n- AMBIL DATA -");
  digitalWrite(buzzer, 0);
  displaydate();
  hapusmenu(40, 52);

  displaydate();
  sensor();

  displaydate();
  Serial.println(F("\r\n- KIRIM DATA KE SERVER THINGSPEAK -"));
  sendServer();

  displaydate();
  Serial.println(F("\r\n- SIMPAN DATA KE MICRO SD-"));
  simpandata();
  delay(2000);

  displaydate();
  tampilKode();

  if (tinggiAir > batas) digitalWrite(buzzer, 1);

  start = millis();
  while (start + 30000 > millis()) {
    displaydate();
    delay(1000);
  }
}
