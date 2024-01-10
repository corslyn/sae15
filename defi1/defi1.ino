// Code par Yousef Hamdi et Enzo Manzinali

// importation des librairies

#include "lightsensor.h"
#include <FastLED.h>
#include "linedriver.h"
#include "carMotors.h"

// initialisation led
const int RGBpin = 4; // pin led
const int numLEDs = 1;
CRGB leds[numLEDs];
uint32_t tabColors[] = {0xFF0000, 0x008000, 0x0000FF, 0xFFA500}; // tableau des couleurs en hexadecimal

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
  Serial.begin(9600); // initialisation moniteur serie a 9600 bauds
  engine.init(speed); //initialisation vitesse initiale
  FastLED.addLeds<NEOPIXEL, RGBpin>(leds, numLEDs); // initialise la led
  FastLED.setBrightness(20); // definit la luminosité de la led
  FastLED.showColor(tabColors[0]); // led rouge
  delay(3000); // delai de 3 secondes
}

void loop() {
  int state = driver.SetLineDriver(sensorL.detectLine(), sensorM.detectLine(), sensorR.detectLine()); // obtient le code des capteurs
  Serial.println(state); // affiche le code d'etat des capteur dans le moniteur serie
  deplacer(state); //deplace la voiture
  switch (cpt) { // changement de la couleur de la led selon le tour
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
  if (cpt < 6) { // tant que le tour 3 n'est pas fini, la voiture bouge
    switch (state) {
      case 0:
        engine.stop(); // pas de ligne
        threshold = 0; // reset de la detection de croisement
        break;
      case 1:

        engine.drive(1, 0.1); // virage serré à droite
        threshold = 0; // reset de la detection de croisement
        break;
      case 2:

        engine.drive(0.8, 0.8); // tout droit
        threshold = 0; // reset de la detection de croisement
        break;
      case 3:

        engine.drive(0.7, 0.3); // virage à droite
        threshold = 0; // reset de la detection de croisement
        break;
      case 4:
        engine.drive(0.1, 1); // virage serré à gauche
        threshold = 0; // reset de la detection de croisement
        break;
      case 6:

        engine.drive(0.3, 0.7); // virage à gauche
        threshold = 0; // reset de la detection de croisement
        break;
      case 7:
        threshold++; 
        if (threshold > 6) { // test si il y a reelement un croisement
          engine.drive(0.8, 0.8); 
          delay(10);// attend un peu avant d'incrementer le compte pour n'en compter qu'un seul
          cpt++; // incremente le compteur de croisement

        } else {
          engine.stop(); // arrete la voiture
        }
        break;
    }
  } else {
    engine.stop(); // fin tour 3
  }
}
