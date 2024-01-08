#include <Arduino.h>
class LineDriver {
private:
    int L0;
    int L1;
    int L2;
public:
    LineDriver(int _L0, int _L1, int _L2) {
        L0 = _L0;
        L1 = _L1;
        L2 = _L2;
    }
    void SetLineDriver(int _L0, int _L1, int _L2) {
        L0 = _L0;
        L1 = _L1;
        L2 = _L2;
        drive();
    }
    int drive() {
        return L0 + 2*L1 + 4*L2;
    }
};