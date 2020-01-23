void inisialisasi() {
  Serial1.begin(9600);  // SIM900A
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);

  display.begin(SSD1306_SWITCHCAPVCC, oled);
  display.clearDisplay();
  display.display();
  delay(10);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.getTextBounds(F("USAID - PDAM"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 0);
  display.println(F("USAID - PDAM"));
  display.getTextBounds(F("WATER LEVEL"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 20);
  display.println(F("WATER LEVEL"));
  display.getTextBounds(F("MONITORING"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 35);
  display.println(F("MONITORING"));
  display.getTextBounds(F("2020"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 50);
  display.println(F("2020"));
  display.display();
}

void tampilanAwal() {
  hapusmenu(17, 64);

  display.getTextBounds(F("LEVEL AIR (mm)"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 20);
  display.println(F("LEVEL AIR (mm)"));
  display.display();
}

void hapusmenu(byte h, byte h1) {
  display.fillRect(0, h, 128, h1, BLACK); //clear display
  display.display();
  display.setTextColor(WHITE, BLACK);
}

void lcd2digits(int number) {
  if (number >= 0 && number < 10) {
    display.write('0');
  }
  display.print(number);
}
