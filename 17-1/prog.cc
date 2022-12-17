#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

enum RockType {FourWide, Plus, Jay, FourTall, Square}; // Tetris, anyone?

bool pushRockToLeft(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
bool pushRockToRight(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
bool rockFalls(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
int fillMatrixWithRock(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);

int main() {
    string jetPattern;
    getline(cin, jetPattern); // There's only one line of input this time, neat!
    int jetIndex = 0;
    int rocksFell = 0;
    vector<vector<bool>> matrix(9000, vector<bool>(7, false)); // Matrix is 7 wide, but infinitely tall. For 2022 rocks, 9000 is probably overkill
    int highestOccupiedIndex = -1;
    RockType rock = FourWide;
    int bottomYValue, leftXValue;

    while (rocksFell < 2022) {
        leftXValue = 2;
        bottomYValue = highestOccupiedIndex + 4; // I know the question says 3 away, but the illustration and example is really 4
        bool atRest = false;
        
        while (!atRest) {
            if (jetPattern[jetIndex] == '<') {
                // Push to the left
                if (pushRockToLeft(rock, matrix, bottomYValue, leftXValue)) {
                    leftXValue--;
                }
            } else {
                // Assume it's a >, which is a push to the right
                if (pushRockToRight(rock, matrix, bottomYValue, leftXValue)) {
                    leftXValue++;
                }
            }

            // Now go one unit down, which may cause us to be at rest
            if (rockFalls(rock, matrix, bottomYValue, leftXValue)) {
                bottomYValue--;
            } else {
                atRest = true;
            }
            jetIndex = ((jetIndex + 1) == jetPattern.length() ? 0 : (jetIndex + 1)); // The winds cycle
        }
        // Mark the matrix
        highestOccupiedIndex = max(highestOccupiedIndex, fillMatrixWithRock(rock, matrix, bottomYValue, leftXValue));

        // Rock processed, change rocks for next iteration
        rocksFell++;
        switch (rock) {
            case FourWide:
                rock = Plus;
                break;
            case Plus:
                rock = Jay;
                break;
            case Jay:
                rock = FourTall;
                break;
            case FourTall:
                rock = Square;
                break;
            case Square:
                rock = FourWide;
                break;
        }
    }

    cout << highestOccupiedIndex + 1 << endl; // 0-indexed tower means need to add 1 to get height

    return 0;
}

bool pushRockToLeft (RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue) {
    // We definitely can't move left if our edge is at the wall
    if (leftXValue == 0) {
        return false;
    }
    switch (rock) {
        case FourWide:
                // Need to check space directly left of the bottom left tile
                return (
                    !matrix[bottomYValue][leftXValue - 1]
                );
            case Plus:
                // Need to check left, bottom, and top tiles
                return (
                    !matrix[bottomYValue][leftXValue] &&
                    !matrix[bottomYValue + 1][leftXValue - 1] &&
                    !matrix[bottomYValue + 2][leftXValue]
                );
            case Jay:
                // Need to check bottom left, as well as the two upper tiles
                return (
                    !matrix[bottomYValue][leftXValue - 1] &&
                    !matrix[bottomYValue + 1][leftXValue + 1] &&
                    !matrix[bottomYValue + 2][leftXValue + 1]
                );
            case FourTall:
                // Need to check every tile
                return (
                    !matrix[bottomYValue][leftXValue - 1] &&
                    !matrix[bottomYValue + 1][leftXValue - 1] &&
                    !matrix[bottomYValue + 2][leftXValue - 1] &&
                    !matrix[bottomYValue + 3][leftXValue - 1]
                );
            case Square:
                // Need to check the left tiles
                return (
                    !matrix[bottomYValue][leftXValue - 1] &&
                    !matrix[bottomYValue + 1][leftXValue - 1]
                );
    }
    // How did we get here
    return false;
}

bool pushRockToRight (RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue) {
    // We do want the bottom right corner instead here
    switch (rock) {
        case FourWide:
                // Need to check space directly right of the bottom right tile
                return (
                    leftXValue + 3 < 6 &&
                    !matrix[bottomYValue][leftXValue + 4]
                );
            case Plus:
                // Need to check right, bottom, and top tiles
                return (
                    leftXValue + 2 < 6 &&
                    !matrix[bottomYValue][leftXValue + 2] &&
                    !matrix[bottomYValue + 1][leftXValue + 3] &&
                    !matrix[bottomYValue + 2][leftXValue + 2]
                );
            case Jay:
                // Need to check bottom right three tiles
                return (
                    leftXValue + 2 < 6 &&
                    !matrix[bottomYValue][leftXValue + 3] &&
                    !matrix[bottomYValue + 1][leftXValue + 3] &&
                    !matrix[bottomYValue + 2][leftXValue + 3]
                );
            case FourTall:
                // Need to check every tile
                return (
                    leftXValue < 6 &&
                    !matrix[bottomYValue][leftXValue + 1] &&
                    !matrix[bottomYValue + 1][leftXValue + 1] &&
                    !matrix[bottomYValue + 2][leftXValue + 1] &&
                    !matrix[bottomYValue + 3][leftXValue + 1]
                );
            case Square:
                // Need to check the right tiles
                return (
                    leftXValue + 1 < 6 &&
                    !matrix[bottomYValue][leftXValue + 2] &&
                    !matrix[bottomYValue + 1][leftXValue + 2]
                );
    }
    // How did we get here
    return false;
}

bool rockFalls (RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue) {
    // If the y value is at 0, it's "rock-bottom"
    if (bottomYValue == 0) {
        return false;
    }
    switch (rock) {
        case FourWide:
                // Need to check every tile
                return (
                    !matrix[bottomYValue - 1][leftXValue] && 
                    !matrix[bottomYValue - 1][leftXValue + 1] && 
                    !matrix[bottomYValue - 1][leftXValue + 2] && 
                    !matrix[bottomYValue - 1][leftXValue + 3]
                );
            case Plus:
                // Need to check right, bottom, and left tiles
                return (
                    !matrix[bottomYValue - 1][leftXValue + 1] &&
                    !matrix[bottomYValue][leftXValue] &&
                    !matrix[bottomYValue][leftXValue + 2]
                );
            case Jay:
                // Need to check bottom three tiles
                return (
                    !matrix[bottomYValue - 1][leftXValue] &&
                    !matrix[bottomYValue - 1][leftXValue + 1] &&
                    !matrix[bottomYValue - 1][leftXValue + 2]
                );
            case FourTall:
                // Need to check only bottom tile
                return (
                    !matrix[bottomYValue - 1][leftXValue]
                );
            case Square:
                // Need to check the bottom tiles
                return (
                    !matrix[bottomYValue - 1][leftXValue] &&
                    !matrix[bottomYValue - 1][leftXValue + 1]
                );
    }
    // How did we get here
    return false;
}

int fillMatrixWithRock(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue) {
    // We'll return the highest Y value that was filled in
    switch (rock) {
        case FourWide:
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue][leftXValue + 2] = true;
                matrix[bottomYValue][leftXValue + 3] = true;
                return bottomYValue;
            case Plus:
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue + 2] = true;
                matrix[bottomYValue + 2][leftXValue + 1] = true;
                return bottomYValue + 2;
            case Jay:
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue][leftXValue + 2] = true;
                matrix[bottomYValue + 1][leftXValue + 2] = true;
                matrix[bottomYValue + 2][leftXValue + 2] = true;
                return bottomYValue + 2;
            case FourTall:
                // Need to check only bottom tile
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue + 2][leftXValue] = true;
                matrix[bottomYValue + 3][leftXValue] = true;
                return bottomYValue + 3;
            case Square:
                // Need to check the bottom tiles
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue + 1] = true;
                return bottomYValue + 1;
    }
    // How did we get here
    return -1;
}