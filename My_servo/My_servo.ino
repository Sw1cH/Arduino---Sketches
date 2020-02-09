// Include the Servo library
#include <Servo.h>
#include "config.h"

// Declare the Servo pin
int servoPin = 2; // D4

// Create a servo object
Servo Servo1;
int servoRotationDegree = 180;

// adafruit
AdafruitIO_Feed *servoButtonFeed = io.feed("BedRoom.servo.button");
AdafruitIO_Feed *servoDegreeFeed = io.feed("BedRoom.servo.rotationDegree");

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial has started");

  // We need to attach the servo to the used pin number
//  Servo1.attach(servoPin);  WE WILL ATTACH IT LATER

  // wait for a connection

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

  // set up a message handler for the 'sharedFeed' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  servoButtonFeed->onMessage(handleMessage);
  servoButtonFeed->get();

  servoDegreeFeed->onMessage(handleDegree);
  servoDegreeFeed->get();
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  delay(2); // to avoid throtling on adafruit

}

void testServo() {
  // Make servo go to 0 degrees
  Servo1.write(0);
  delay(1000);
  Serial.println("Make servo go to 0 degrees");

  // Make servo go to 90 degrees
  Servo1.write(90);
  delay(1000);
  Serial.println("Make servo go to 90 degrees");

  // Make servo go to 180 degrees
  Servo1.write(180);
  delay(1000);
  Serial.println(" Make servo go to 180 degrees");
}

void rotateServo(int degree) {
  Servo1.attach(servoPin);
  Servo1.write(degree);
  delay(1000);
  Serial.print("Make servo go to degree ");
  Serial.println(degree);
  Servo1.detach();
}

// this function is called whenever an 'sharedFeed' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("push received <-  ");
  int push = data->toInt();
  Serial.println(push);

  if (push == 1) {
    rotateServo(180 - servoRotationDegree);
//    rotateServo(0);
  }
}

void handleDegree(AdafruitIO_Data *data) {

  Serial.print("degree received <-  ");
  servoRotationDegree = data->toInt();
  Serial.println(servoRotationDegree);
}
