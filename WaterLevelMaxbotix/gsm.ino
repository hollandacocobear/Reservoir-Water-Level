void initGSM() {
  hapusmenu(17, 64);
  display.getTextBounds(F("CEK MODUL GSM"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 20);
  display.println(F("CEK MODUL GSM"));
  display.display();
  delay(1000);

  Serial.println(F("\r\nAT+CSCLK=0"));
  Serial1.println(F("AT+CSCLK=0"));
  bacaserial(200);
  Serial.flush();
  Serial1.flush();

  //CONNECT AT
  for (a = 0; a < 6; a++) {
    b = ConnectAT(F("AT"), 100);
    if (b == 8) {
      hapusmenu(40, 64);
      display.getTextBounds(F("MODUL GSM OK!!"), 0, 0, &posx, &posy, &w, &h);
      display.setCursor((128 - w) / 2, 40);
      display.println(F("MODUL GSM OK!!"));
      display.display();
      Serial.println(F("MODUL GSM OK!!"));
      Serial.flush();
      Serial1.flush();
      break;
    }
    if (b < 8) {
      display.getTextBounds(F("MODUL GSM ERROR!!"), 0, 0, &posx, &posy, &w, &h);
      display.setCursor((128 - w) / 2, 40);
      display.println(F("MODUL GSM ERROR!!"));
      display.display();
      Serial.println(F("MODUL GSM ERROR"));
      Serial.flush();
      Serial1.flush();

      if (a == 5) {
        display.getTextBounds(F("CONTACT CS!!!"), 0, 0, &posx, &posy, &w, &h);
        display.setCursor((128 - w) / 2, 63 - 8);
        display.println(F("CONTACT CS!!!"));
        display.display();
        Serial.println(F("CONTACT CS!!!"));
        Serial.flush();
        Serial1.flush();
        while (1);
      }
    }
    delay(1000);
  }
  delay(1000);

  Serial.println(F("\r\nAT+CPIN?"));
  Serial1.println(F("AT+CPIN?"));
  bacaserial(200);
  Serial.println(F("\r\nAT+CFUN=1"));
  Serial1.println(F("AT+CFUN=1"));
  bacaserial(200);
  Serial.println(F("\r\nAT+CBAND=\"ALL_BAND\""));
  Serial1.println(F("AT+CBAND=\"ALL_BAND\""));
  bacaserial(200);
  delay(5000);
}

void cekOperator() {
  hapusmenu(30, 64);
  display.getTextBounds(F("OPERATOR"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 35);
  display.println(F("OPERATOR"));
  display.display();
  delay(1000);

  c = 0;
cops:
  filename = "";
  Serial.println(F("\r\nAT+CREG=1"));
  Serial1.println(F("AT+CREG=1"));
  bacaserial(200);
  delay(500);

  Serial.println(F("\r\nAT+COPS?"));
  Serial1.println(F("AT+COPS?"));
  Serial.flush();
  Serial1.flush();
  delay(200);
  while (Serial1.available() > 0) {
    if (Serial1.find("+COPS:")) {
      while (Serial1.available() > 0) {
        g = Serial1.read();
        filename += g;
      }
    }
  }
  Serial.flush();
  Serial1.flush();

  a = filename.indexOf('"');
  b = filename.indexOf('"', a + 1);
  y = filename.substring(a + 1, b);
  if (y == "51089") y = "THREE";

  operators = y;
  Serial.println(y);
  Serial.flush();
  delay(100);

  //option if not register at network
  if (operators == "")  {
    c++;
    if (c == 15) {
      Serial.println(F("- OPERATOR TIDAK DITEMUKAN -"));
      display.getTextBounds(F("OPERATOR TIDAK ADA"), 0, 0, &posx, &posy, &w, &h);
      display.setCursor((128 - w) / 2, 50);
      display.println(F("OPERATOR TIDAK ADA"));
      display.display();
      while (1);
    }
    goto cops;
  }

  display.getTextBounds((char*)operators.c_str(), 0, 0, &posx, &posy, &w, &h); //(char*)WiFi.SSID().c_str()
  display.setCursor((128 - w) / 2, 50);
  display.println(operators);
  display.display();
}

void cekSinyal() {
  hapusmenu(30, 64);
  display.getTextBounds(F("SIGNAL"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 35);
  display.println(F("SIGNAL"));
  display.display();

signals:
  filename = "";
  Serial.println(F("\r\nAT+CSQ"));
  Serial1.println(F("AT+CSQ"));
  Serial.flush();
  Serial1.flush();
  delay(200);
  while (Serial1.available() > 0) {
    if (Serial1.find("+CSQ: ")) {
      while (Serial1.available() > 0) {
        g = Serial1.read();
        Serial.print(g);
        filename += g;
      }
    }
  }
  Serial.println(" ");
  Serial.println(filename);
  Serial.flush();
  Serial1.flush();

  a = (filename.substring(0, filename.indexOf(','))).toInt();
  Serial.print(a);
  Serial.print(" ");
  Serial.flush();
  if (a < 10) {
    network = "POOR";
  }
  if (a > 9 && a < 15) {
    network = "FAIR";
  }
  if (a > 14 && a < 20) {
    network = "GOOD";
  }
  if (a > 19 && a <= 31) {
    network = "EXCELLENT";
  }
  if (a == 99) {
    network = "UNKNOWN";
    goto signals;
  }
  Serial.println(network);
  delay(100);

  display.getTextBounds((char*)network.c_str(), 0, 0, &posx, &posy, &w, &h); //(char*)WiFi.SSID().c_str()
  display.setCursor((128 - w) / 2, 50);
  display.println(network);
  display.display();
  network = "";
}

void bacaserial(int wait) {
  result = "";
  start = millis();
  while ((start + wait) > millis()) {
    while (Serial1.available() > 0) {
      g = Serial1.read();
      Serial.print(g);
      result += g;
    }
  }
}

void tampilKode() {
  if (kode != 200) {
    network = "Err";
  }
  if (w == 200) {
    network = "OK";
  }
  display.getTextBounds((char*)network.c_str(), 0, 0, &posx, &posy, &w, &h); //(char*)WiFi.SSID().c_str()
  display.setCursor((128 - w), 63 - 8);
  display.println(network);
  delay(1000);
}

byte ConnectAT(String cmd, int d) {
  i = 0;
  while (1) {
    Serial1.println(cmd);
    while (Serial1.available()) {
      if (Serial1.find("OK"))
        i = 8;
    }
    delay(d);
    if (i > 5) {
      break;
    }
    i++;
  }
  return i;
}

void sendServer() {
  kode = 0;
  network = "";

  Serial.println(F("\r\nAT+CGATT=1"));
  Serial1.println(F("AT+CGATT=1"));
  bacaserial(200);
  delay(1000);

  //DEAKTIVASI GPRSPDP CONTEXT DAN TUTUP BEARER
  Serial.println(F("\r\nAT+CIPSHUT;+SAPBR=0,1"));
  Serial1.println(F("AT+CIPSHUT;+SAPBR=0,1"));
  bacaserial(500);
  delay(1000);

  //CONNECTION TYPE = GPRS ; ATUR APN, USER, DAN PASSWORD
  Serial.println(F("\r\nAT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));
  Serial1.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));
  bacaserial(200);
  delay(1000);

  //APN ID
  result = "AT+SAPBR=3,1,\"APN\",\"" + String(GPRS_APN) + "\"";
  Serial.println("");
  Serial.println(result);
  Serial1.println(result);
  Serial1.flush();
  bacaserial(200);
  Serial.flush();
  Serial1.flush();
  delay(1000);

  //APN USER
  displaydate();
  result = "AT+SAPBR=3,1,\"USER\",\"" + String(GPRS_USER) + "\"";
  Serial.println("");
  Serial.println(result);
  Serial1.println(result);
  bacaserial(200);
  Serial.flush();
  Serial1.flush();
  delay(1000);

  //APN PASSWORD
  displaydate();
  result = "AT+SAPBR=3,1,\"PWD\",\"" + String(GPRS_PASS) + "\"";
  Serial.println("");
  Serial.println(result);
  Serial1.println(result);
  bacaserial(200);
  Serial.flush();
  Serial1.flush();
  delay(1000);

  //OPEN BEARER
  displaydate();
  Serial.println(F("\r\nAT+SAPBR=1,1"));
  Serial1.println(F("AT+SAPBR=1,1"));
  delay(200);
  cekserial(30000);
  delay(1000);

  //OPEN BEARER
  displaydate();
  Serial.println(F("\r\nAT+SAPBR=2,1"));
  Serial1.println(F("AT+SAPBR=2,1"));
  delay(200);
  bacaserial(5000);
  delay(1000);

  //HTTP TERM
  Serial.println(F("\r\nAT+HTTPTERM"));
  Serial1.println(F("AT+HTTPTERM"));
  bacaserial(200);
  delay(1000);

  //HTTP INIT
  Serial.println(F("\r\nAT+HTTPINIT"));
  Serial1.println(F("AT+HTTPINIT"));
  bacaserial(200);
  delay(1000);

  Serial.println(F("AT+HTTPPARA=\"CID\",1"));
  Serial1.println(F("AT+HTTPPARA=\"CID\",1"));
  delay(200);
  y = String(tinggiAir / 1000.00, 3);
  // untuk POST http://api.thingspeak.com/update.json?api_key=MN3RFZ7MK4HNUPD7&field1=0.925
  result = "AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/update?api_key=";
  result += SECRET_WRITE_APIKEY + "&field1=";
  result += y + "\"";
  Serial.println(result);
  Serial1.println(result);
  delay(200);
  bacaserial(200);
  delay(1000);

  Serial.println("AT+HTTPACTION=0");
  Serial1.println("AT+HTTPACTION=0");
  bacaserial(500);

  Serial.println("AT+HTTPREAD");
  Serial1.println("AT+HTTPREAD");
  delay(1000);
bacaserial(6000);

  a = 0; b = 0;
  a = result.indexOf(',', 1);
  b = result.indexOf(',', a+1);
  Serial.println(a);
  Serial.println(b);
  y = result.substring(a+1 , a + 4);
  Serial.println(y);
  kode = y.toInt();
  Serial.print("Kode=");
  Serial.println(kode);
  statuscode(kode);
}

void cekserial(unsigned int times) {
  boolean indeks = 0;
  char karakter;
  unsigned long mulai = millis();
  while (millis() - mulai < times) {
    //    Serial.println(millis()-mulai);
    while (Serial1.available() > 0) {
      karakter = Serial1.read();
      Serial.print(karakter);
      if (karakter == 'O' || karakter == 'E') {
        indeks = 1;
        break;
      }

    }
    if (indeks == 1) break;
  }
}

void tungguGSM() {
  hapusmenu(17, 64);
  display.setTextSize(2);
  display.setTextColor(WHITE);


  for (i = 60; i < 0; i--) {
    result = String(i);
    hapusmenu(40, 64);
    display.getTextBounds(result.c_str(), 0, 0, &posx, &posy, &w, &h);
    display.setCursor((panjang - w) / 2, 40);
    display.print(result);
    display.display();
    delay(1000);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void statuscode(int w) {
  if (w == 0) {
    network = "Error";
  }

  if (w == 100) {
    network = "Continue";
  }
  if (w == 101) {
    network = "Switching Protocols";
  }
  if (w == 200) {
    network = "OK";
  }
  if (w == 201) {
    network = "Created";
  }
  if (w == 202) {
    network = "Accepted";
  }
  if (w == 203) {
    network = "Non-Authoritative Information";
  }
  if (w == 204) {
    network = "No Content";
  }
  if (w == 205) {
    network = "Reset Content";
  }
  if (w == 206) {
    network = "Partial Content";
  }
  if (w == 300) {
    network = "Multiple Choices";
  }
  if (w == 301) {
    network = "Moved Permanently";
  }
  if (w == 302) {
    network = "Found";
  }
  if (w == 303) {
    network = "See Other";
  }
  if (w == 304) {
    network = "Not Modified";
  }
  if (w == 305) {
    network = "Use Proxy";
  }
  if (w == 307) {
    network = "Temporary Redirect";
  }
  if (w == 400) {
    network = "Bad Request";
  }
  if (w == 401) {
    network = "Unauthorized";
  }
  if (w == 402) {
    network = "Payment Required";
  }
  if (w == 403) {
    network = "Forbidden";
  }
  if (w == 404) {
    network = "Not Found";
  }
  if (w == 405) {
    network = "Method Not Allowed";
  }
  if (w == 406) {
    network = "Not Acceptable";
  }
  if (w == 407) {
    network = "Proxy Authentication Required";
  }
  if (w == 408) {
    network = "Request Time-out";
  }
  if (w == 409) {
    network = "Conflict";
  }
  if (w == 410) {
    network = "Gone";
  }
  if (w == 411) {
    network = "Length Required";
  }
  if (w == 412) {
    network = "Precondition Failed";
  }
  if (w == 413) {
    network = "Request Entity Too Large";
  }
  if (w == 414) {
    network = "Request-URI Too Large";
  }
  if (w == 415) {
    network = "Unsupported Media Type";
  }
  if (w == 416) {
    network = "Requested range not satisfiable";
  }
  if (w == 417) {
    network = "Expectation Failed ";
  }
  if (w == 500) {
    network = "Internal Server Error";
  }
  if (w == 501) {
    network = "Not Implemented";
  }
  if (w == 502) {
    network = "Bad Gateway";
  }
  if (w == 503) {
    network = "Service Unavailable";
  }
  if (w == 504) {
    network = "Gateway Time-out";
  }
  if (w == 505) {
    network = "HTTP Version not supported";
  }
  if (w == 600) {
    network = "Not HTTP PDU";
  }
  if (w == 601) {
    network = "Network Error";
  }
  if (w == 602) {
    network = "No memory";
  }
  if (w == 603) {
    network = "DNS Error";
  }
  if (w == 604) {
    network = "Stack Busy";
  }
}
