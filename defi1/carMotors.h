#include <Arduino.h>

#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

class CarMotors {
private:
  uint8_t currentSpeed; // vitesse courante des deux moteurs
  bool isMoving; // état du robot, avance (true) ou est arrêté (false)
public :
// initialisation des ports pour commander les moteurs
  void init(uint8_t p_speed);
// réglage de la vitesse de rotation  
  void setSpeed(uint8_t p_speed) { currentSpeed = p_speed; }
// fait avancer la voiture
  void goForward();
// fait reculer la voiture
  void goBackward();
// fait tourner la voiture sur place vers la gauche
  void turnLeft();
// fait tourner la voiture sur place vers la droite
  void turnRight();
  // fait rouler la voiture en indiquant la vitesses de roues de gauche et des roues de droite.
  void drive(float leftCoef,float rightCoef);
  void stop();
  bool getIsMoving() { return isMoving; }
};