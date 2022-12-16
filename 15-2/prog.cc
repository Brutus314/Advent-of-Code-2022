#include <iostream>
#include <unordered_set>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX_TO_CARE_ABOUT = 4000000;
//const int MAX_TO_CARE_ABOUT = 20;

int main () {
    string junk;
    int sX, sY, bX, bY;
    unordered_set<int> occupiedSpaces;
    unordered_set<int> beaconsXValueOnCaredRow;

    // Contains ranges at each y value
    vector<vector<int>> xLeftBounds(MAX_TO_CARE_ABOUT + 1, vector<int>()), xRightBounds(MAX_TO_CARE_ABOUT + 1, vector<int>());

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

        // Keep an eye on which ranges we fill at each y level
        for (int y = max(0, sY - range); y <= min(MAX_TO_CARE_ABOUT, sY + range); y++) {
            int rangeAtThisRow = range - abs(sY - y);
            
            xLeftBounds[y].push_back(max(0, sX - rangeAtThisRow));
            xRightBounds[y].push_back(min(MAX_TO_CARE_ABOUT, sX + rangeAtThisRow));
        }
    }

    // The idea here is we will "Defragment" all our ranges
    // First, order the ranges in left bound order, tiebreaking on right bound
    // Then, using the first range as a base, compare it to each other range
    // The comparing range MUST have its left bound either below the current right bound, or 1 higher than it (adjacent)
    //   If this is violeted, then it is likely the hole we are looking for
    //   The x value we skipped combined with the current y value yield the answer
    // Take the comparing right range, and if it is greater than the current right range, set the current right range equal to it
    // If we make it through the set of ranges, then it isn't that Y value

    for (int y = 0; y < MAX_TO_CARE_ABOUT; y++) {
        // First: sort the ranges
        vector<int> tempLeft, tempRight;
        for (int i = 0; i < xLeftBounds[y].size(); i++) {
            int minIndex = i;
            for (int j = i + 1; j < xLeftBounds[y].size(); j++) {
                if (xLeftBounds[y][j] < xLeftBounds[y][minIndex]) {
                    minIndex = j;
                } else if (xLeftBounds[y][j] == xLeftBounds[y][minIndex] && xRightBounds[y][j] < xRightBounds[y][minIndex]) {
                    minIndex = j;
                }
            }
            int tempLeft = xLeftBounds[y][i], tempRight = xRightBounds[y][i];
            xLeftBounds[y][i] = xLeftBounds[y][minIndex];
            xRightBounds[y][i] = xRightBounds[y][minIndex];
            xLeftBounds[y][minIndex] = tempLeft;
            xRightBounds[y][minIndex] = tempRight;
        }

        // Now let's compare each other range to the first one
        for (int i = 1; i < xLeftBounds[y].size(); i++) {
            if (xLeftBounds[y][i] - xRightBounds[y][0] <= 1) {
                if (xRightBounds[y][i] > xRightBounds[y][0]) {
                    xRightBounds[y][0] = xRightBounds[y][i];
                }
            } else {
                // BUZZER, but we need to prep for a BEEG number
                long long outx = xRightBounds[y][0] + 1;
                long long constValue = 4000000;
                long long outy = y;
                cout << (outx * constValue) + y << endl;
                return 0;
            }
        }
    }

    cout << "Error" << endl;

    return 0;
}