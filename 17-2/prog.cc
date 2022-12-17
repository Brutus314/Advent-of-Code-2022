#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

const long long ROCKS_TO_FALL = 1000000000000;

enum RockType {FourWide, Plus, Jay, FourTall, Square}; // Tetris, anyone?

// We are in a repeating state IF:
//    The top of our board is a pattern we've seen before
//    We've seen the top of that board after dropping the same type of rock
//    We've seen the top of that board after going through the same jet index

class BoardState {
    private:
        int _x0, _x1, _x2, _x3, _x4, _x5, _x6; // Stores the 0-normalized top-level blocks AFTER the previous block fell, BEFORE the next block falls
        RockType _rock; // Will store what the NEXT rock that falls will be
        int _jetIndex; // Will store what the NEXT jet action index is
    
    public:
        int height; // Stores the height of the board, not used in comparison but will be necessary later
        BoardState(vector<int> xValues, RockType rock, int jetIndex);
        bool operator==(BoardState other);
};

bool pushRockToLeft(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
bool pushRockToRight(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
bool rockFalls(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue);
void fillMatrixWithRock(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue, vector<int>& highestOccupiedIndices);

int maxInList(vector<int> list) {
    int m = list[0];
    for (int i = 1; i < list.size(); i++) {
        if (list[i] > m) {
            m = list[i];
        }
    }
    return m;
}

int minInList(vector<int> list) {
    int m = list[0];
    for (int i = 1; i < list.size(); i++) {
        if (list[i] < m) {
            m = list[i];
        }
    }
    return m;
}

int main() {
    string jetPattern;
    getline(cin, jetPattern); // There's only one line of input this time, neat!
    int jetIndex = 0;
    long long rocksFell = 0;
    vector<vector<bool>> matrix(9000, vector<bool>(7, false)); // Matrix is 7 wide, but infinitely tall. For 2022 rocks, 9000 is probably overkill
    vector<int> highestOccupiedIndices(7, -1);
    RockType rock = FourWide;
    int bottomYValue, leftXValue;

    bool patternFound = false;
    vector<BoardState> knownStates;
    knownStates.push_back(BoardState(highestOccupiedIndices, rock, jetIndex));
    int foundState = -1;
    long long loopedHeightToAdd = 0;

    while (rocksFell < ROCKS_TO_FALL) {
        leftXValue = 2;
        bottomYValue = maxInList(highestOccupiedIndices) + 4; // I know the question says 3 away, but the illustration and example is really 4
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
        fillMatrixWithRock(rock, matrix, bottomYValue, leftXValue, highestOccupiedIndices);

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
        if (foundState == -1) {
            // See if we've seen this state before
            BoardState thisState(highestOccupiedIndices, rock, jetIndex);
            for (int i = 0; i < knownStates.size(); i++) {
                if (knownStates[i] == thisState) {
                    foundState = i;
                    break;
                }
            }
            if (foundState > -1) {
                long long loopingHeight = thisState.height - knownStates[foundState].height;
                long long loopDuration = rocksFell - foundState;
                long long completeLoops = (ROCKS_TO_FALL - rocksFell) / loopDuration;
                long long remainingRocks = (ROCKS_TO_FALL - rocksFell) % loopDuration;
                loopedHeightToAdd += (completeLoops * loopingHeight);
                rocksFell = ROCKS_TO_FALL - remainingRocks;
            } else {
                knownStates.push_back(BoardState(highestOccupiedIndices, rock, jetIndex));
            }
        }
    }

    cout << maxInList(highestOccupiedIndices) + 1 + loopedHeightToAdd << endl; // 0-indexed tower means need to add 1 to get height
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

void fillMatrixWithRock(RockType rock, vector<vector<bool>>& matrix, int bottomYValue, int leftXValue, vector<int>& highestOccupiedIndices) {
    // We'll return the highest Y value that was filled in
    switch (rock) {
        case FourWide:
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue][leftXValue + 2] = true;
                matrix[bottomYValue][leftXValue + 3] = true;

                highestOccupiedIndices[leftXValue] = max(highestOccupiedIndices[leftXValue], bottomYValue);
                highestOccupiedIndices[leftXValue + 1] = max(highestOccupiedIndices[leftXValue + 1], bottomYValue);
                highestOccupiedIndices[leftXValue + 2] = max(highestOccupiedIndices[leftXValue + 2], bottomYValue);
                highestOccupiedIndices[leftXValue + 3] = max(highestOccupiedIndices[leftXValue + 3], bottomYValue);
                return;
            case Plus:
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue + 2] = true;
                matrix[bottomYValue + 2][leftXValue + 1] = true;

                highestOccupiedIndices[leftXValue] = max(highestOccupiedIndices[leftXValue], bottomYValue + 1);
                highestOccupiedIndices[leftXValue + 1] = max(highestOccupiedIndices[leftXValue + 1], bottomYValue + 2);
                highestOccupiedIndices[leftXValue + 2] = max(highestOccupiedIndices[leftXValue + 2], bottomYValue + 1);
                return;
            case Jay:
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue][leftXValue + 2] = true;
                matrix[bottomYValue + 1][leftXValue + 2] = true;
                matrix[bottomYValue + 2][leftXValue + 2] = true;

                highestOccupiedIndices[leftXValue] = max(highestOccupiedIndices[leftXValue], bottomYValue);
                highestOccupiedIndices[leftXValue + 1] = max(highestOccupiedIndices[leftXValue + 1], bottomYValue);
                highestOccupiedIndices[leftXValue + 2] = max(highestOccupiedIndices[leftXValue + 2], bottomYValue + 2);
                return;
            case FourTall:
                // Need to check only bottom tile
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue + 2][leftXValue] = true;
                matrix[bottomYValue + 3][leftXValue] = true;

                highestOccupiedIndices[leftXValue] = max(highestOccupiedIndices[leftXValue], bottomYValue + 3);
                return;
            case Square:
                // Need to check the bottom tiles
                matrix[bottomYValue][leftXValue] = true;
                matrix[bottomYValue + 1][leftXValue] = true;
                matrix[bottomYValue][leftXValue + 1] = true;
                matrix[bottomYValue + 1][leftXValue + 1] = true;

                highestOccupiedIndices[leftXValue] = max(highestOccupiedIndices[leftXValue], bottomYValue + 1);
                highestOccupiedIndices[leftXValue + 1] = max(highestOccupiedIndices[leftXValue + 1], bottomYValue + 1);
                return;
    }
}

BoardState::BoardState(vector<int> xValues, RockType rock, int jetIndex) {
    int minYValue = minInList(xValues);
    height = maxInList(xValues) + 1;
    _x0 = xValues[0] - minYValue;
    _x1 = xValues[1] - minYValue;
    _x2 = xValues[2] - minYValue;
    _x3 = xValues[3] - minYValue;
    _x4 = xValues[4] - minYValue;
    _x5 = xValues[5] - minYValue;
    _x6 = xValues[6] - minYValue;
    _rock = rock;
    _jetIndex = jetIndex;
}

bool BoardState::operator==(BoardState other) {
    return (
        _x0 == other._x0 &&
        _x1 == other._x1 &&
        _x2 == other._x2 &&
        _x3 == other._x3 &&
        _x4 == other._x4 &&
        _x5 == other._x5 &&
        _x6 == other._x6 &&
        _rock == other._rock &&
        _jetIndex == other._jetIndex
    );
}