#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

bool sandLogic(vector<vector<bool>>& occupied);

int main () {
    string input;
    string junk;
    stringstream lineInput;
    int maxY = 0;
    int curX, curY;
    int newX, newY;
    int smallX, smallY, bigX, bigY;
    vector<vector<bool>> occupied(1000, vector<bool>(1000, false)); // Overkill

    // Go until end of input
    while (getline(cin, input)) {
        curX = -1;
        curY = -1;
        lineInput = stringstream(input);

        // Go until the end of this line
        while (lineInput >> newX) {
            lineInput.ignore(); // Ignore the comma
            lineInput >> newY;

            lineInput >> junk; // Ignore the arrow
            if (curX == -1) {
                // This is the first pair
                curX = newX;
                curY = newY;
            } else {
                // Time to "draw"
                // The direction of drawing doesn't matter, so we'll just go "up"
                smallX = min(curX, newX);
                bigX = max(curX, newX);
                smallY = min(curY, newY);
                bigY = max(curY, newY);
                // One of the x or y pairs will be the same, ensuring that loop is only iterated once
                for (int i = smallX; i <= bigX; i++) {
                    for (int j = smallY; j <= bigY; j++) {
                        occupied[j][i] = true; // Looks backwards here
                    }
                }
                curX = newX;
                curY = newY;
            }
            if (curY > maxY) {
                maxY = curY;
            }
        }
    }
    // Add the floor
    for (int i = 0; i < 1000; i++) {
        occupied[maxY + 2][i] = true;
    }
    
    int count = 0;
    while (sandLogic(occupied)) {
        count++;
    }

    cout << count << endl;

    return 0;
}

bool sandLogic(vector<vector<bool>>& occupied) {
    int posX = 500;

    if (!occupied[0][500]) {
        int i = 0;
        while (true) {
            if (occupied[i][posX]) {
                if (!occupied[i][posX - 1]) {
                    // Check to the left
                    posX--;
                } else if (!occupied[i][posX + 1]) {
                    // Check to the right
                    posX++;
                } else {
                    // We are on an occupied spot, but we couldn't have gone around. Should have stopped one up
                    occupied[i - 1][posX] = true;
                    return true;
                }
            }
            i++;
        }
    } else {
        // It was occupied
        return false;
    }
}