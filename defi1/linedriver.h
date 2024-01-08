#include <Arduino.h>

class LineDriver {
private:
    int L0;
    int L1;
    int L2;

public:
    // Default constructor with default values
    LineDriver(int _L0 = 0, int _L1 = 0, int _L2 = 0) {
        L0 = _L0;
        L1 = _L1;
        L2 = _L2;
    }

    // ... rest of the class remains unchanged

    int SetLineDriver(int _L0, int _L1, int _L2) {
    L0 = _L0;
    L1 = _L1;
    L2 = _L2;
    return drive();  // Return the result of the drive calculation.
}


    int drive() {
        return L0 + 2 * L1 + 4 * L2;
    }
};
