#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include "step.hpp"

using namespace std;

int main() {
    string input;
    vector<vector<Step>> terrain;
    int lines = 0;
    pair<int, int> endingSpot;
    queue<Step> toCheck;

    // Go until end of input
    // Note that because of how vectors work to store the data, x and y may look reversed here
    while (getline(cin, input) && input.length() > 0) {
        terrain.push_back(vector<Step>());
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == 'S' || input[i] == 'a') {
                Step potentialStart(i, lines, 'a');
                potentialStart.minStepsToReach = 0;
                terrain[lines].push_back(potentialStart);
                toCheck.push(potentialStart);
            } else if (input[i] == 'E') {
                endingSpot = make_pair(lines, i);
                terrain[lines].push_back(Step(i, lines, 'z'));
            } else {
                terrain[lines].push_back(Step(i, lines, input[i]));
            }
        }
        lines++;
    }

    // Do a path finding algorithm: visit a spot, then check all unvisited spots that can be reached from this spot
    // Using a queue to analyze visited spots in shortest-path order
    // With equal weight, if we know the shortest path to the current spot, then the unvisited spots must have a shortest path through this spot

    while (!toCheck.empty()) {
        Step checkingSpot = toCheck.front();
        toCheck.pop();

        // Need to check to the left = -x
        if (checkingSpot.x > 0 && 
            terrain[checkingSpot.y][checkingSpot.x - 1].minStepsToReach == -1 && 
            (terrain[checkingSpot.y][checkingSpot.x - 1].elevation - checkingSpot.elevation <= 1)
        ) {
            terrain[checkingSpot.y][checkingSpot.x - 1].minStepsToReach = checkingSpot.minStepsToReach + 1;
            toCheck.push(terrain[checkingSpot.y][checkingSpot.x - 1]);
        }

        // Up = -y
        if (checkingSpot.y > 0 && 
            terrain[checkingSpot.y - 1][checkingSpot.x].minStepsToReach == -1 && 
            (terrain[checkingSpot.y - 1][checkingSpot.x].elevation - checkingSpot.elevation <= 1)
        ) {
            terrain[checkingSpot.y - 1][checkingSpot.x].minStepsToReach = checkingSpot.minStepsToReach + 1;
            toCheck.push(terrain[checkingSpot.y - 1][checkingSpot.x]);
        }

        // Right = +x
        if (checkingSpot.x < (terrain[0].size() - 1) && 
            terrain[checkingSpot.y][checkingSpot.x + 1].minStepsToReach == -1 && 
            (terrain[checkingSpot.y][checkingSpot.x + 1].elevation - checkingSpot.elevation <= 1)
        ) {
            terrain[checkingSpot.y][checkingSpot.x + 1].minStepsToReach = checkingSpot.minStepsToReach + 1;
            toCheck.push(terrain[checkingSpot.y][checkingSpot.x + 1]);
        }

        // Down = +y
        if (checkingSpot.y < (terrain.size() - 1) && 
            terrain[checkingSpot.y + 1][checkingSpot.x].minStepsToReach == -1 && 
            (terrain[checkingSpot.y + 1][checkingSpot.x].elevation - checkingSpot.elevation <= 1)
        ) {
            terrain[checkingSpot.y + 1][checkingSpot.x].minStepsToReach = checkingSpot.minStepsToReach + 1;
            toCheck.push(terrain[checkingSpot.y + 1][checkingSpot.x]);
        }
    }

    cout << terrain[endingSpot.first][endingSpot.second].minStepsToReach << endl;

    return 0;
}