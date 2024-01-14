#include <Arduino.h>

// Classe pour utiliser un capteur IR
class LightSensor {
private:
    int pin; // Pin où le capteur est branché

public:
// Constructeur
    LightSensor(int pinSensor) {
        pin = pinSensor;
        // lecture analogique du pin
        pinMode(pin, INPUT);
    }

    int detectLine() { //méthode de détection d'une ligne
        int sensorValue = analogRead(pin); // lecture de la valeur analogique renvoyée par le capteur IR
    
        if (sensorValue > 600) { // réglage de la sensibilité du capteur
            return 1;
        } else {
            return 0;
        }
    }
};
