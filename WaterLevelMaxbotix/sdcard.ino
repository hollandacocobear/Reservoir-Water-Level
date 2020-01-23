void sdInit() {
  hapusmenu(17, 64);
  display.getTextBounds(F("- CEK SD Card -"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 20);
  display.println(F("- CEK SD Card -"));
  display.display();
  pinMode(SSpin, OUTPUT);
  digitalWrite(SSpin, HIGH);
  delay(2000);
  if (!SD.begin(SSpin)) { //SD ERROR
    Serial.println(F("- SD CARD error!!! -"));
    Serial.flush();
    display.getTextBounds(F("SD Card Error!!!"), 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 40);
    display.println(F("SD Card Error!!!"));
    display.display();
    while (1);
  }

  Serial.println(F("- SD CARD INIT OK! -"));
  Serial.flush();
  display.getTextBounds(F("SD Card OK!"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 40);
  display.println(F("SD Card OK!"));
  display.display();
}

void dateTime(uint16_t* date, uint16_t* time) {
  nows = rtc.now();
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(nows.year(), nows.month(), nows.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(nows.hour(), nows.minute(), nows.second());
}

void simpandata() {
  SdFile::dateTimeCallback(dateTime);
  filename = "";
  filename = String(tahun);
  if (bulan < 10) {
    filename += "0" + String(bulan);
  }
  if (bulan >= 10) {
    filename += String(bulan);
  }
  if (hari < 10) {
    filename += "0" + String(hari);
  }
  if (hari >= 10) {
    filename += String(hari);
  }
  filename += ".txt";

  Serial.println(filename);
  Serial.flush();

  displaydate();
  file = SD.open(filename, FILE_READ);
  a = file.available();
  file.close();

  // set date time callback function
  SdFile::dateTimeCallback(dateTime);
  file = SD.open(filename, FILE_WRITE);
  if (a == 0) {
    Serial.println(filename);
    file.print(F("TANGGAL (YYYY/MM/DD HH:MM:SS),"));
    file.println(F(" KETINGGIAN AIR (METER), KODE NETWORK, RESPON"));
  }

  y = "";
  y = String(tahun) + '/';
  if (bulan < 10) {
    y += "0" + String(bulan);
  }
  if (bulan >= 10) {
    y += String(bulan);
  }
  y += "/";
  if (hari < 10) {
    y += "0" + String(hari);
  }
  if (hari >= 10) {
    y += String(hari);
  }
  y += " ";
  if (jam < 10) {
    y += "0" + String(jam);
  }
  if (jam >= 10) {
    y += String(jam);
  }
  y += ":";
  if (menit < 10) {
    y += "0" + String(menit);
  }
  if (menit >= 10) {
    y += String(menit);
  }
  y += ":";
  if (detik < 10) {
    y += "0" + String(detik);
  }
  if (detik >= 10) {
    y += String(detik);
  }
  y += ", " + String(tinggiAir) + ", " ;
  y += String(kode) + ", " + network;
  Serial.println(y);
  file.println(y);
  file.sync();
  file.close();
  displaydate();
}
