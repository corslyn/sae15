#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

const int RGBpin = 4;
const int numLEDs = 1;
CRGB leds[numLEDs];
uint32_t tabColors[] = {0xFF0000, 0xFB4C0D, 0x00FF00};

LightSensor sensorL(A0);
LightSensor sensorM(A1);
LightSensor sensorR(A2);

LineDriver driver;

CarMotors engine;

void setup() {
    Serial.begin(9600);
    
    Serial.println("Start...");
}

void loop() {
    int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine());
    Serial.println(state);
    delay(100);
}
