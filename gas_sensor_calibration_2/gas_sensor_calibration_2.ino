#include <LiquidCrystal_I2C.h>
#include <MQ135.h>

const int ANALOGPIN=0;
MQ135 gasSensor = MQ135(ANALOGPIN);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float rzero;

void setup(){
  lcd.init(); 
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  Serial.begin(9600);
  rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
}

void loop(){
  float rzero = gasSensor.getRZero();
  Serial.println(rzero);
  delay(1000);

  lcd.setCursor(0,0);
  lcd.print("RZERO : ");
  lcd.print(rzero);
}
