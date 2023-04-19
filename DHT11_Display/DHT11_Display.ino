/*!
 * @file readDHT11.ino
 * @brief DHT11 is used to read the temperature and humidity of the current environment. 
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2018-09-14
 * @url https://github.com/DFRobot/DFRobot_DHT11
 */

#include <DFRobot_DHT11.h>

// include the library code:
#include <LiquidCrystal.h>

DFRobot_DHT11 DHT;
#define DHT11_PIN 7

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define custom characters for up, down, and sideways arrows
byte up_arrow[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
byte down_arrow[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};
byte sideways_arrow[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};

float prev_temp = 0.0;
float prev_humidity = 0.0;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  // create custom characters
  lcd.createChar(0, up_arrow);
  lcd.createChar(1, down_arrow);
  lcd.createChar(2, sideways_arrow);
}

void loop() {
  DHT.read(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(DHT.temperature);
  lcd.print("  H:");
  lcd.print(DHT.humidity);

  lcd.setCursor(0, 1);
  lcd.write("T:");
  if(DHT.temperature > prev_temp) {
    lcd.write(byte(0)); // up arrow
  } else if(DHT.temperature < prev_temp) {
    lcd.write(byte(1)); // down arrow
  } else {
    lcd.write(byte(2)); // sideways arrow
  }
lcd.write("   H:");
  if(DHT.humidity > prev_humidity) {
    lcd.write(byte(0)); // up arrow
  } else if(DHT.humidity < prev_humidity) {
    lcd.write(byte(1)); // down arrow
  } else {
    lcd.write(byte(2)); // sideways arrow
  }

  prev_temp = DHT.temperature;
  prev_humidity = DHT.humidity;

  lcd.display();
  delay(1000);
}
