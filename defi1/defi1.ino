#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

LightSensor sensorL(A0);
LightSensor sensorM(A1);
LightSensor sensorR(A2);

LineDriver driver;

CarMotors engine;

void setup() {
    Serial.begin(9600);
    engine.init(200);
}
void loop() {

}