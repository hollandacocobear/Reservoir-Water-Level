void rtcinit() {
  hapusmenu(15, 64);
  display.getTextBounds(F("INIT CLOCK"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 20);
  display.println(F("INIT CLOCK"));
  display.display();
  delay(2000);

  if (! rtc.begin() || rtc.lostPower()) { // RTC NOT BEGIN
    Serial.println(F("-RTC TIDAK DITEMUKAN -"));
    Serial.flush();
    display.getTextBounds(F("ERROR!! CONTACT CS."), 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 40);
    display.println(F("ERROR!! CONTACT CS."));
    display.display();
    while (1);
  }

  nows = rtc.now();
  interval = nows.second();
  while (nows.second() < interval + 3) {
    nows = rtc.now();
    filename = String(nows.month()) + '/' + String(nows.day()) + '/' + String(nows.year()) + ' ' + String(nows.hour()) + ':' + String(nows.minute()) + ':' + String(nows.second());
    Serial.println(filename);
    display.getTextBounds(F("yyyy/mm/dd hh:mm:ss"), 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 40);
    display.print(nows.year());
    display.print("/");
    lcd2digits(nows.month());
    display.print("/");
    lcd2digits(nows.day());
    display.print(" ");
    lcd2digits(nows.hour());
    display.print(":");
    lcd2digits(nows.minute());
    display.print(":");
    lcd2digits(nows.second());
    display.display();
    delay(200);
  }
}

void displaydate() {
  nows = rtc.now();
  nows = rtc.now();
  tahun = nows.year();
  bulan = nows.month();
  hari = nows.day();
  jam = nows.hour();
  menit = nows.minute();
  detik = nows.second();

  display.getTextBounds(F("yyyy/mm/dd hh:mm "), 0, 0, &posx, &posy, &w, &h);
  display.setTextColor(WHITE, BLACK);
  display.setCursor((128 - w), 0);
  display.print(nows.year()); display.print("/");
  lcd2digits(nows.month()); display.print("/");
  lcd2digits(nows.day()); display.print(" ");
  lcd2digits(nows.hour()); display.print(":");
  lcd2digits(nows.minute());
  display.display();

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
  Serial.println("");
  Serial.println(y);
}
