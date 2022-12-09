#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

void fixKnots(vector<pair<int, int>>& knots, unordered_map<string, bool>& visitedSpots);

int main() {
    char direction;
    int distance;
    unordered_map<string, bool> visitedSpots;

    // knots[n].first = x, knots[n].second = y
    vector<pair<int, int>> knots(10, pair(0, 0));
    visitedSpots.insert_or_assign("0,0", true);

    // Go until end of input
    while (cin >> direction >> distance) {
        // U = +y, R = +x, D = -y, L = -x
        if (direction == 'U') {
            for (int i = 0; i < distance; i++) {
                knots[0].second++;
                fixKnots(knots, visitedSpots);
            }
        } else if (direction == 'R') {
            for (int i = 0; i < distance; i++) {
                knots[0].first++;
                fixKnots(knots, visitedSpots);
            }
        } else if (direction == 'D') {
            for (int i = 0; i < distance; i++) {
                knots[0].second--;
                fixKnots(knots, visitedSpots);
            }
        } else {
            // L
            for (int i = 0; i < distance; i++) {
                knots[0].first--;
                fixKnots(knots, visitedSpots);
            }
        }
    }

    cout << visitedSpots.size() << endl;
}

void fixKnots(vector<pair<int, int>>& knots, unordered_map<string, bool>& visitedSpots) {
    // Fix each position based on the one before it
    for (int i = 1; i < knots.size(); i++) {
        int xDiff = knots[i - 1].first - knots[i].first;
        int yDiff = knots[i - 1].second - knots[i].second;

        // Knots can move diagonally now, violating both axis. Move by 1 step in each axis to correct
        if (abs(xDiff) > 1 && abs(yDiff) > 1) {
            if (xDiff > 0) {
                // Will be one less
                knots[i].first = knots[i - 1].first - 1;
            } else {
                // Will be one more
                knots[i].first = knots[i - 1].first + 1;
            }
            if (yDiff > 0) {
                // Will be one less
                knots[i].second = knots[i - 1].second - 1;
            } else {
                // Will be one more
                knots[i].second = knots[i - 1].second + 1;
            }
        }
        else if (abs(xDiff) > 1) {
            if (yDiff != 0) {
                // Y axis will become the same
                knots[i].second = knots[i - 1].second;
            }
            if (xDiff > 0) {
                // Will be one less
                knots[i].first = knots[i - 1].first - 1;
            } else {
                // Will be one more
                knots[i].first = knots[i - 1].first + 1;
            }
        } else if (abs(yDiff) > 1) {
            if (xDiff != 0) {
                // X axis will become the same
                knots[i].first = knots[i - 1].first;
            }
            if (yDiff > 0) {
                // Will be one less
                knots[i].second = knots[i - 1].second - 1;
            } else {
                // Will be one more
                knots[i].second = knots[i - 1].second + 1;
            }
        } else {
            // Optimazation: if we don't need to fix a knot, then we also don't need to fix knots after it
            break;
        }
        if (i == knots.size() - 1) {
            visitedSpots.insert_or_assign(to_string(knots[i].first) + "," + to_string(knots[i].second), true);
        }
    }
}