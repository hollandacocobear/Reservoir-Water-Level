void sensor() {
  reads = analogRead(pinTekanan);
  tinggiAir = reads * 5; //satuan milimeter

  result = String(tinggiAir);
  hapusmenu(35,64);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.getTextBounds(result.c_str(), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2,35);
  display.print(result);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Serial.print(F("TINGGI AIR (MM) = "));
  Serial.println(tinggiAir);

}
