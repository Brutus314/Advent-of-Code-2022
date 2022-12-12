#ifndef AOC_STEP
#define AOC_STEP

struct Step {
    public:
        int x;
        int y;
        char elevation;
        int minStepsToReach;

        Step(int initialX, int initialY, char initialElevation) {
            x = initialX;
            y = initialY;
            elevation = initialElevation;
            minStepsToReach = -1; // -1 serves to let us know if it has been visited yet
        }
};

#endif