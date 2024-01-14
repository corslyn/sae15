#include <Arduino.h>

// classe pour déterminer la situation du robot selon les capteus
class LineDriver {
private:
// situation de chaque capteur (voit une ligne ou non)
    int L0;
    int L1;
    int L2;

public:
    // constructeur
    LineDriver(int _L0 = 0, int _L1 = 0, int _L2 = 0) {
        L0 = _L0;
        L1 = _L1;
        L2 = _L2;
    }

    

    int SetLineDriver(int _L0, int _L1, int _L2) { //méthode pour configurer la fonction drive() selon les valeurs des capteurs
        L0 = _L0;
        L1 = _L1;
        L2 = _L2;
        return drive();  // renvoie le code donné par drive()
    }


    int drive() {
        return L0 + 2 * L1 + 4 * L2; // renvoie le code décimal correspondant à la situation du robot
    }
};
