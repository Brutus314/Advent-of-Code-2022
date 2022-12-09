#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <string>

using namespace std;

void fixTailPos(int headPosX, int headPosY, int& tailPosX, int& tailPosY, unordered_map<string, bool>& visitedSpots);

int main() {
    char direction;
    int distance;
    unordered_map<string, bool> visitedSpots;

    int headPosX = 0, headPosY = 0, tailPosX = 0, tailPosY = 0;
    visitedSpots.insert_or_assign("0,0", true);

    // Go until end of input
    while (cin >> direction >> distance) {
        // U = +y, R = +x, D = -y, L = -x
        if (direction == 'U') {
            for (int i = 0; i < distance; i++) {
                headPosY++;
                fixTailPos(headPosX, headPosY, tailPosX, tailPosY, visitedSpots);
            }
        } else if (direction == 'R') {
            for (int i = 0; i < distance; i++) {
                headPosX++;
                fixTailPos(headPosX, headPosY, tailPosX, tailPosY, visitedSpots);
            }
        } else if (direction == 'D') {
            for (int i = 0; i < distance; i++) {
                headPosY--;
                fixTailPos(headPosX, headPosY, tailPosX, tailPosY, visitedSpots);
            }
        } else {
            // L
            for (int i = 0; i < distance; i++) {
                headPosX--;
                fixTailPos(headPosX, headPosY, tailPosX, tailPosY, visitedSpots);
            }
        }
    }

    cout << visitedSpots.size() << endl;
}

void fixTailPos(int headPosX, int headPosY, int& tailPosX, int& tailPosY, unordered_map<string, bool>& visitedSpots) {
    int xDiff = headPosX - tailPosX;
    int yDiff = headPosY - tailPosY;

    // We should only be violating one axis at a time, since we cannot move the head diagonally
    if (abs(xDiff) > 1) {
        if (yDiff != 0) {
            // Y axis will become the same
            tailPosY = headPosY;
        }
        if (xDiff > 0) {
            // Will be one less
            tailPosX = headPosX - 1;
        } else {
            // Will be one more
            tailPosX = headPosX + 1;
        }
    } else if (abs(yDiff) > 1) {
        if (xDiff != 0) {
            // X axis will become the same
            tailPosX = headPosX;
        }
        if (yDiff > 0) {
            // Will be one less
            tailPosY = headPosY - 1;
        } else {
            // Will be one more
            tailPosY = headPosY + 1;
        }
    }
    visitedSpots.insert_or_assign(to_string(tailPosX) + "," + to_string(tailPosY), true);
}