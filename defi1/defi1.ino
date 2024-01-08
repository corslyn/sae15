
#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

const int RGBpin = 4;
const int numLEDs = 1;
CRGB leds[numLEDs];
uint32_t tabColors[] = {0xFF0000, 0xFB4C0D, 0x00FF00};

LightSensor sensorL(A2);
LightSensor sensorM(A1);
LightSensor sensorR(A0);

LineDriver driver;

CarMotors engine;
int cpt = 0;
double speed = 235;
void setup() {
  Serial.begin(9600);
  engine.init(speed);
  Serial.println("Start...");
}

void loop() {

  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
  Serial.println(state);
  if (cpt<6) {
  switch (state) {
    case 0:
      engine.stop();
      break;
    case 1:
      engine.setSpeed(speed / 2);
      engine.turnLeft();
      break;
    case 2:
      engine.setSpeed(speed);
      engine.goForward();
      break;
    case 3:
      engine.setSpeed(speed / 2);
      engine.turnLeft();
      break;
    case 4:
      engine.setSpeed(speed / 2);
      engine.turnRight();
      break;
    case 6:
      engine.setSpeed(speed / 2);
      engine.turnRight();
      break;
    case 7:
      cpt += 1;
      engine.goForward();
      break;
  }
  } else {
  engine.stop();
  }
}
