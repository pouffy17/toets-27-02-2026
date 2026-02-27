#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 5);  // SDA = 4, SCL = 5

  lcd.init();
  lcd.backlight();

  dht.begin();

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 niet gevonden!");
    lcd.print("BMP280 ERROR");
  }

  lcd.clear();
  lcd.print("Thermometer");
  delay(2000);
}

void loop() {
  float binnenTemp = bmp.readTemperature();
  float buitenTemp = dht.readTemperature();

  Serial.print("Binnen: ");
  Serial.print(binnenTemp);
  Serial.print("  Buiten: ");
  Serial.println(buitenTemp);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("In: ");
  lcd.print(binnenTemp, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Out: ");
  lcd.print(buitenTemp, 1);
  lcd.print((char)223);
  lcd.print("C");

  delay(2000);
}