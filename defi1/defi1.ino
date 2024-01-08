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
double speed = 235;

void setup() {
  Serial.begin(9600);
  engine.init(speed);
  Serial.println("Start...");
  FastLED.addLeds<NEOPIXEL, RGBpin>(leds, numLEDs);  // led
  FastLED.setBrightness(20);                           // led
  delay(3000);
}

void loop() {
  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
  Serial.println(state);

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
      engine.goForward();
      threshold++;
      if (threshold > 5) {
        cpt++;
      }
      break;
  }

  if (threshold != 0 && threshold < 5) {
    threshold = 0;
  }



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
      engine.stop();  // Stop the engine when cpt reaches 6
      break;
  }
} //bing chilling
