#include "intInMods.hpp"

IntInMods::IntInMods(int initial) {
    _inMod2 = initial % 2;
    _inMod3 = initial % 3;
    _inMod5 = initial % 5;
    _inMod7 = initial % 7;
    _inMod11 = initial % 11;
    _inMod13 = initial % 13;
    _inMod17 = initial % 17;
    _inMod19 = initial % 19;
    _inMod23 = initial % 23;
}

void IntInMods::squareMyself() {
    _inMod2 = (_inMod2 * _inMod2) % 2;
    _inMod3 = (_inMod3 * _inMod3) % 3;
    _inMod5 = (_inMod5 * _inMod5) % 5;
    _inMod7 = (_inMod7 * _inMod7) % 7;
    _inMod11 = (_inMod11 * _inMod11) % 11;
    _inMod13 = (_inMod13 * _inMod13) % 13;
    _inMod17 = (_inMod17 * _inMod17) % 17;
    _inMod19 = (_inMod19 * _inMod19) % 19;
    _inMod23 = (_inMod23 * _inMod23) % 23;
}

bool IntInMods::isDivisibleBy(int operand) {
    switch(operand) {
        case 2:
            return _inMod2 == 0;
        case 3:
            return _inMod3 == 0;
        case 5:
            return _inMod5 == 0;
        case 7:
            return _inMod7 == 0;
        case 11:
            return _inMod11 == 0;
        case 13:
            return _inMod13 == 0;
        case 17:
            return _inMod17 == 0;
        case 19:
            return _inMod19 == 0;
        case 23:
            return _inMod23 == 0;
        default:
            return false;
    }
}

IntInMods IntInMods::operator+(int operand) {
    _inMod2 = (_inMod2 + operand) % 2;
    _inMod3 = (_inMod3 + operand) % 3;
    _inMod5 = (_inMod5 + operand) % 5;
    _inMod7 = (_inMod7 + operand) % 7;
    _inMod11 = (_inMod11 + operand) % 11;
    _inMod13 = (_inMod13 + operand) % 13;
    _inMod17 = (_inMod17 + operand) % 17;
    _inMod19 = (_inMod19 + operand) % 19;
    _inMod23 = (_inMod23 + operand) % 23;

    return *(this);
}

IntInMods IntInMods::operator*(int operand) {
    _inMod2 = (_inMod2 * operand) % 2;
    _inMod3 = (_inMod3 * operand) % 3;
    _inMod5 = (_inMod5 * operand) % 5;
    _inMod7 = (_inMod7 * operand) % 7;
    _inMod11 = (_inMod11 * operand) % 11;
    _inMod13 = (_inMod13 * operand) % 13;
    _inMod17 = (_inMod17 * operand) % 17;
    _inMod19 = (_inMod19 * operand) % 19;
    _inMod23 = (_inMod23 * operand) % 23;

    return *(this);
}