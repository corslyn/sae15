#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

// initialisation de la led

const int RGBpin = 4;
const int numLEDs = 1;
CRGB leds[numLEDs];
uint32_t tabColors[] = {0xFF0000, 0x008000, 0x0000FF, 0xFFA500};

// initialisation des capteurs IR

LightSensor sensorL(A2);
LightSensor sensorM(A1);
LightSensor sensorR(A0);

// initialisation de la classe linedriver et des moteurs

LineDriver driver;
CarMotors engine;

int cpt = 0; // compteur d'intersection
int threshold = 0; // determine si un croisement est reelement present (anti faux positif)
int speed = 200; // vitesse max

void setup() {
  Serial.begin(9600);
  engine.init(speed); //initialisation vitesse initiale
  FastLED.addLeds<NEOPIXEL, RGBpin>(leds, numLEDs);
  FastLED.setBrightness(20);
  FastLED.showColor(tabColors[0]); // led rouge
  delay(3000);
}

void loop() {
  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine()); // obtient le code des capteurs
  Serial.println(state);
  deplacer(state);
  switch (cpt) {
    case 0:
      FastLED.showColor(tabColors[1]); // led verte au tour 1
      break;
    case 2:
      FastLED.showColor(tabColors[2]); // led bleue au tour 2
      break;
    case 4:
      FastLED.showColor(tabColors[3]); // led orange au tour 3
      break;
    case 6:
      FastLED.showColor(tabColors[0]); // led rouge à la fin
      break;
  }
}

void deplacer(int state) {
  if (cpt < 6) {
    switch (state) {
      case 0:
        engine.stop(); // pas de ligne
        threshold = 0; 
        break;
      case 1:

        engine.drive(1, 0.1); // virage serré à droite
        threshold = 0;
        break;
      case 2:

        engine.drive(0.8, 0.8); // tout droit
        threshold = 0;
        break;
      case 3:

        engine.drive(0.7, 0.3); // virage à droite
        threshold = 0;
        break;
      case 4:
        engine.drive(0.1, 1); // virage serré à gauche
        threshold = 0;
        break;
      case 6:

        engine.drive(0.3, 0.7); // virage à gauche
        threshold = 0;
        break;
      case 7:
        threshold++; 
        if (threshold > 6) { // est ce que c'est reelement un croisement ?
          engine.drive(0.8, 0.8);
          delay(10);
          cpt++; // incremente le compteur de croisement

        } else {
          engine.stop();
        }
        break;
    }
  } else {
    engine.stop(); // fin tour 3
  }
}
