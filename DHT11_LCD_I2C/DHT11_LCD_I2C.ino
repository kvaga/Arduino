

#include <SimpleDHT.h>
# include <Wire.h>
# include <LiquidCrystal_I2C.h>
// https://github.com/johnrickman/LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, 16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display




// for DHT11, 
//      VCC: 5V or 3V
//      GND: GNDc:\
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;
char lcd_temperature_text[256];
char lcd_humidity_text[256];

void setup() {
  Serial.begin(9600);
  lcd.init();                     // initialize the lcd
}

void lcd_print_th(const char* row1, const char* row2){
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(row1);
  lcd.setCursor(1,1);
  lcd.print(row2);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};

  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  
  sprintf(lcd_temperature_text, "%d\xDF Temperature", (int)temperature);
  sprintf(lcd_humidity_text, "%d%% Humidity",(int)humidity);
  Serial.print(lcd_temperature_text);
  Serial.print(lcd_humidity_text);
  lcd_print_th(lcd_temperature_text,lcd_humidity_text);
    
  // DHT11 sampling rate is 1HZ.
  delay(1000);
}
