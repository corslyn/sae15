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
double speed = 200;

void setup() {
  Serial.begin(9600);
  engine.init(speed);
  Serial.println("Start...");
  FastLED.addLeds<NEOPIXEL, RGBpin>(leds, numLEDs);
  FastLED.setBrightness(20);
  FastLED.showColor(tabColors[0]);

  delay(3000);
}

void loop() {
  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
  Serial.println(state);
  deplacer(state);
  switch (cpt) {
    case 0:
      FastLED.showColor(tabColors[1]);
      break;
    case 2:
      FastLED.showColor(tabColors[2]);
      break;
    case 4:
      FastLED.showColor(tabColors[3]);
      break;
    case 6:
      FastLED.showColor(tabColors[0]);
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

        engine.drive(1, 0.1);
        threshold = 0;
        break;
      case 2:

        engine.drive(0.8, 0.8);
        threshold = 0;
        break;
      case 3:

        engine.drive(0.7, 0.3);
        threshold = 0;
        break;
      case 4:
        engine.drive(0.1, 1);
        threshold = 0;
        break;
      case 6:

        engine.drive(0.3, 0.7);
        threshold = 0;
        break;
      case 7:
        threshold++;
        if (threshold > 5) {
          engine.drive(0.8, 0.8);
          delay(10);
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
