#include <Arduino.h>

class LightSensor {
private:
    int pin;

public:
    LightSensor(int pinSensor) {
        pin = pinSensor;
        pinMode(pin, INPUT);
    }

    int detectLine() {
        int sensorValue = analogRead(pin);
      
        // Calibrate these threshold values based on your sensor and lighting conditions
        if (sensorValue > 300 && sensorValue < 800) {
            return 1;
        } else {
            return 0;
        }
    }
};
