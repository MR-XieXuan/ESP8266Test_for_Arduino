//Arduino OLED Example
#include <Arduino.h>
#include <U8g2lib.h>
#include <stdlib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define OLED_SCL D4
#define OLED_SDA D3

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_SCL,OLED_SDA, U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"HELLOW WORLD!");
  u8g2.sendBuffer();
  delay(1000);
}
