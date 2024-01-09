#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

const int RGBpin = 4;
const int numLEDs = 1;
CRGB leds[numLEDs];
uint32_t tabColors[] = {0xFF0000, 0x008000, 0x0000FF, 0xFFA500};

LightSensor sensorL(A2);
LightSensor sensorM(A1);
LightSensor sensorR(A0);

LineDriver driver;

CarMotors engine;
int cpt = 0;
int threshold = 0;
double speed = 180;

void setup() {
  Serial.begin(9600);
  engine.init(speed);
  Serial.println("Start...");
  FastLED.addLeds<NEOPIXEL, RGBpin>(leds, numLEDs);
  FastLED.setBrightness(20);
  delay(3000);
}

void loop() {
  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
  Serial.println(state);
  deplacer(state);
  switch (cpt) {
    case 0:
      FastLED.showColor(tabColors[0]);
      break;
    case 2:
      FastLED.showColor(tabColors[1]);
      break;
    case 4:
      FastLED.showColor(tabColors[2]);
      break;
    case 6:
      FastLED.showColor(tabColors[3]);
      break;
  }
}

void deplacer(int state) {
  if (cpt < 6) {
    switch (state) {

      case 0:
        engine.stop();
        threshold = 0;
        break;
      case 1:
        engine.setSpeed(speed / 2);
        engine.turnLeft();
        threshold = 0;
        break;
      case 2:
        engine.setSpeed(speed);
        engine.goForward();
        threshold = 0;
        break;
      case 3:
        engine.setSpeed(speed / 2);
        engine.turnLeft();
        threshold = 0;
        break;
      case 4:
        engine.setSpeed(speed / 2);
        engine.turnRight();
        threshold = 0;
        break;
      case 6:
        engine.setSpeed(speed / 2);
        engine.turnRight();
        threshold = 0;
        break;
      case 7:

        threshold++;
        if (threshold > 5) {
          engine.goForward();
          cpt++;
        } else {
          engine.stop();
        }
        break;

    }
  } else {
    engine.stop();
  }
}
