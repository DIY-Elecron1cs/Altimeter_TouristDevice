#include <GyverBME280.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(6, 7, 8); //CLK, DAT, RST

GyverBME280 bme;

byte GRAD[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte Elbrus1[8] = {
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01111, 0b10000
};
byte Elbrus2[8] = {
  0b00000, 0b00000, 0b00001, 0b00010, 0b01100, 0b10000, 0b00111, 0b01000
};
byte Elbrus3[8] = {
  0b00000, 0b11000, 0b00110, 0b00001, 0b11101, 0b00000, 0b00000, 0b00000
};
byte Elbrus4[8] = {
  0b00011, 0b00110, 0b11111, 0b10111, 0b00000, 0b01000, 0b00100, 0b11110
};
byte Elbrus5[8] = {
  0b00000, 0b11100, 0b00111, 0b10001, 0b00000, 0b10000, 0b00000, 0b00000
};
byte Elbrus6[8] = {
  0b00000, 0b00000, 0b00000, 0b10000, 0b01100, 0b00111, 0b00011, 0b00001
};

void setup() {
  //myRTC.setDS1302Time(00, 36, 11, 06, 27, 07, 2024);
  bme.begin();
  lcd.init();
  lcd.backlight();

  lcd.createChar(1, Elbrus1);
  lcd.createChar(2, Elbrus2);
  lcd.createChar(3, Elbrus3);
  lcd.createChar(4, Elbrus4);
  lcd.createChar(5, Elbrus5);
  lcd.createChar(6, Elbrus6);

  lcd.setCursor(5, 0);             //вывод на дисплей логотипа
  lcd.print("\1\2\3\4\5\6");
  lcd.setCursor(2, 1);
  lcd.print("Elbrus mount");
  delay(3000);
  lcd.clear();
}

void loop() {
  drawBME();
  delay(4000);
  drawTime();
  delay(4000);
}

void drawBME() {       //вывод на дисплей показаний с BME280

  lcd.clear();

  lcd.createChar(7, GRAD);
  lcd.setCursor(0, 0);
  lcd.print("t: ");
  lcd.setCursor(3, 0);
  lcd.print(int(bme.readTemperature()));
  lcd.setCursor(5, 0);
  lcd.print("\7C");

  lcd.setCursor(8, 0);
  lcd.print("h: ");
  lcd.setCursor(11, 0);
  lcd.print(int(bme.readHumidity()));
  lcd.setCursor(13, 0);
  lcd.print("%");

  float pressure = bme.readPressure();
  lcd.setCursor(0, 1);
  lcd.print("p: ");
  lcd.setCursor(3, 1);
  lcd.print(int(pressureToMmHg(pressure)));
  lcd.setCursor(6, 1);
  lcd.print("mm");

  lcd.setCursor(10, 1);
  lcd.print(int(pressureToAltitude(pressure)));
  lcd.setCursor(15, 1);
  lcd.print("m");
}

void drawTime () {       //вывод на дисплей времени и даты

  lcd.clear();

  myRTC.updateTime();
  lcd.setCursor(0, 0);
  lcd.print("date: ");
  lcd.print(myRTC.dayofmonth);
  lcd.print(".");
  lcd.print(myRTC.month);
  lcd.print(".");
  lcd.print(myRTC.year);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("time: ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  lcd.println("   ");
}
