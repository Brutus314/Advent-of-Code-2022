#ifndef AOC_INT_IN_MODS
#define AOC_INT_IN_MODS

class IntInMods {
    private:
        int _inMod2;
        int _inMod3;
        int _inMod5;
        int _inMod7;
        int _inMod11;
        int _inMod13;
        int _inMod17;
        int _inMod19;
        int _inMod23;

    public:
        IntInMods(int initial);

        void squareMyself();
        IntInMods operator+(int operand);
        IntInMods operator*(int operand);
        bool isDivisibleBy(int operand); // We will only expect this to be called with 2, 3, 5, 7, 11, 13, 17, or 19
};

#endif