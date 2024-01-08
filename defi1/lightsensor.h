#include <Arduino.h>

class LightSensor {
  private:
	int pin;
  public:
  LightSensor(int pinSensor) {
	pin = pinSensor;
	pinMode(pin, INPUT);
	detectLine();
  }

  int detectLine() {
	float state = digitalRead(pin);
	if (state>0) {
  	return 1;
	} else {
  	return 0;
	}
  }
};
