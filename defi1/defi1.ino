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

void setup() {
    Serial.begin(9600);
    engine.init(100);
    Serial.println("Start...");
}

void loop() {

    int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
    Serial.println(state);
    switch(state) {
      case 0:
        engine.stop();
        break;
      case 1:
        engine.setSpeed(60);
        engine.turnLeft();
                delay(100);
        engine.goForward();

        break;
      case 2:
        engine.setSpeed(100);
        engine.goForward();
        break;
      case 3:
        engine.setSpeed(60);
        
        engine.turnLeft();
                delay(100);
        engine.goForward();

        break;
      case 4:
        engine.setSpeed(60);
        engine.turnRight();
                delay(100);
        engine.goForward();

        break;
      case 6:
        engine.setSpeed(60);
        engine.turnRight();
        delay(100);
                engine.goForward();

        break;
      case 7:
        engine.stop();
        break;

        
    }
    delay(100);
}
