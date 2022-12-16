#include <iostream>
#include <unordered_set>
#include <string>
#include <cstdlib>

using namespace std;

//const int LEVEL_TO_CARE_ABOUT = 10;
const int LEVEL_TO_CARE_ABOUT = 2000000;

int main () {
    string junk;
    int sX, sY, bX, bY;
    unordered_set<int> occupiedSpaces;
    unordered_set<int> beaconsXValueOnCaredRow;

    // Go until end of input
    while (cin >> junk) { // Sensor
        cin >> junk >> junk; // at x={NUM}
        sX = stoi(junk.substr(2, junk.length() - 3)); // Sensor x parsed
        cin >> junk; // y={NUM};
        sY = stoi(junk.substr(2, junk.length() - 3)); // Sensor y parsed
        cin >> junk >> junk >> junk >> junk >> junk; // closest beacon is at x={num},
        bX = stoi(junk.substr(2, junk.length() - 3)); // Beacon x parsed
        cin >> junk; // y={num}
        bY = stoi(junk.substr(2, junk.length() - 2)); // Beacon y parsed

        int range = abs(sX - bX) + abs(sY - bY);
        int rangeAtTargetRow = range - abs(sY - LEVEL_TO_CARE_ABOUT);

        for (int i = sX - rangeAtTargetRow; i <= sX + rangeAtTargetRow; i++) {
            occupiedSpaces.insert(i);
        }
        if (bY == LEVEL_TO_CARE_ABOUT) {
            beaconsXValueOnCaredRow.insert(bX);
        }
        
    }

    cout << occupiedSpaces.size() - beaconsXValueOnCaredRow.size() << endl;

    return 0;
}