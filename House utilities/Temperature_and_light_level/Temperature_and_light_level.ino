// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int tempPin = A0;   // named constant for the pin the sensor is connected to
int photocellPin = A1;    // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider

#define BUTTON_PIN A5    // The number of the push-button pin.
#define LCD_LIGHT_PIN A4 // The number of the pin where anode of the display backlight is.
#define LCD_LIGHT_ON_TIME 10000 // How long (in milliseconds) should lcd light stay on?

unsigned int currentLcdLightOnTime = 0;
unsigned long lcdLightOn_StartMillis; // For calculating the lcd light on time.
boolean isLcdLightOn;
int buttonState = 0; // For checking push-button state

void setup() {
  Serial.begin(9600);     // Other baud rates can be used...
  lcd.begin(16, 2);       // Print a message to the LCD.
  
  pinMode(BUTTON_PIN, INPUT);  // Set the push-button pin as an input.
  pinMode(LCD_LIGHT_PIN, OUTPUT); // Set the lcd display backlight anode pin to low - lcd light off.
  digitalWrite(LCD_LIGHT_PIN, LOW);
  isLcdLightOn = false;
}

void loop() { 
  checkIfBtnPressed();
  checkTemp();
  checkLight();
  delay(500);
}

void checkIfBtnPressed(){
  buttonState = digitalRead(BUTTON_PIN);       // Check the state of the push-button.
 
  if (buttonState == HIGH){       // Button pressed.
    Serial.println("Button pressed - HIGH");
    lcdLightOn_StartMillis = millis();
    currentLcdLightOnTime = 0;
    isLcdLightOn = true;
    digitalWrite(LCD_LIGHT_PIN, HIGH);
  } else {
    // Button not pressed.
    Serial.println("Button not pressed - LOW");
    if(isLcdLightOn){
      currentLcdLightOnTime = millis() - lcdLightOn_StartMillis;
      if(currentLcdLightOnTime > LCD_LIGHT_ON_TIME){
        isLcdLightOn = false;
        digitalWrite(LCD_LIGHT_PIN, LOW);
      }
    }
  }
  Serial.print("Lcd light on time: ");
  Serial.println(currentLcdLightOnTime);
}

void checkTemp() {
    int tempVal = analogRead(tempPin);    // read the value on AnalogIn pin 0 and store it in a variable
  
  float voltage = (tempVal / 1024.0) * 5.0; // convert the ADC reading to voltage

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((voltage - 500 mV) times 100)
  
  float temperature = (voltage - .5) * 100;
  String tempString = String("Temp: " + String(temperature) + "c");

  lcd.setCursor(0, 0);        // Show temp on first LCD line
  lcd.print(tempString);
  Serial.print("Temperature ");
  Serial.println(tempString);
}

void checkLight() {
  photocellReading = analogRead(photocellPin);  // read the value on AnalogIn pin A1 and store it in a variable

  Serial.print("Raw reading = ");
  Serial.println(photocellReading);     
  photocellReading = map(photocellReading, 0, 1023, 0, 99);
  Serial.print("Mapped reading = ");
  Serial.print(photocellReading);

  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 20) {
    Serial.println(" - Dark");
  } else if (photocellReading < 40) {
    Serial.println(" - Dim");
  } else if (photocellReading < 60) {
    Serial.println(" - Light");
  } else if (photocellReading < 80) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  String lightString = String("Light lvl: " + String(photocellReading)+ "% ");
  lcd.setCursor(0, 1);    // Show temp on 2nd LCD line
  lcd.print(lightString);
}

