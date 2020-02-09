#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQ135.h>
#define ANALOGPIN A0    //  Define Analog PIN on Arduino Board
#define RZERO 206.85    //  Define RZERO Calibration Value

MQ135 gasSensor = MQ135(ANALOGPIN);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float rzero;

void setup()
{
  lcd.init(); 
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  Serial.begin(9600);
 rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
}

void loop()
{
  float ppm = gasSensor.getPPM();
  rzero = gasSensor.getRZero();
  delay(1000);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  Serial.print("RZero value:");
  Serial.println(rzero);
  
  lcd.setCursor(0,0);
  lcd.print("PPM :");
  lcd.print(ppm);
  lcd.setCursor(0,1);
  lcd.print("RZERO : ");
  lcd.print(rzero);
}
