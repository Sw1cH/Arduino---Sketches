#include <LiquidCrystal_I2C.h>
#include <MQ135.h>
#include "config.h"

//#include "DHT.h"
//#define DHTTYPE DHT11
//#define DHTPIN 7
//DHT dht(DHTPIN, DHTTYPE);

//#include <dht11.h>
//#define DHT11PIN 4
//dht11 DHT11;


#include <dht.h>
int dht_dpin = A1; //no ; here. Set equal to channel sensor is on
dht DHT;

// Gas sensor
const int ANALOGPIN = 0;
MQ135 gasSensor = MQ135(ANALOGPIN);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// adafruit
AdafruitIO_Feed *gasFeed = io.feed("BedRoom.gasSensor.ppm");

void setup() {
  lcd.init();
  lcd.begin(16, 2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  Serial.begin(115200);

//  dht.begin();
  
   // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}


void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  printAirQuality();
  printDHT11readings();
}

void printAirQuality() {
  float ppm = gasSensor.getPPM();
  char message[] = "TEST" ;
  Serial.println(ppm);
//  lcd.setCursor(0, 1);
//  lcd.print(message);
  delay(1000);

  if (350 > ppm) {
    char message[] = "Fresh, nigga";
    lcd.setCursor(0, 1);
    lcd.print(message);
  }
  if ((350 < ppm) && (450 > ppm))
  {
    char message[] = "Healthy, normal outside";
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else if ((450 < ppm) && (600 > ppm))
  {
    char message[] = "Acceptable level";
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else if ((600 < ppm) && (1000 > ppm))
  {
    char message[] = "Complains of stiffness and odors";
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else if ((1000 < ppm) && (2500 > ppm))
  {
    char message[] = "General drowsiness";
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else if ((2500 < ppm) && (5000 > ppm))
  {

    char message[] = "< 8 hours";
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else if (5000 < ppm)
  {
    char message[] = "Extreme";
    lcd.setCursor(0, 1);
    lcd.print(message);
  }

  lcd.setCursor(0, 0);
  lcd.print("CO2 ppm : ");
  lcd.print(ppm);

  // IO
  gasFeed->save(ppm);

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);
 
}

void printDHT11readings()
{
//float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  float f = dht.readTemperature(true);
//
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }
//
//  float hif = dht.computeHeatIndex(f, h);
//  float hic = dht.computeHeatIndex(t, h, false);
//
//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));



//  Serial.println();
//
//  int chk = DHT11.read(DHT11PIN);
//
//  Serial.print("Humidity (%): ");
//  Serial.println((float)DHT11.humidity, 2);
//
//  Serial.print("Temperature (C): ");
//  Serial.println((float)DHT11.temperature, 2);
//

  DHT.read11(dht_dpin);

    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
  delay(800);//Don't try to access too frequently... in theory
  //should be once per two seconds, fastest,
  //but seems to work after 0.8 second.



}
