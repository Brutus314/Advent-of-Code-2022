#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int maxPressure(vector<int>& flowRates, vector<vector<int>>& shortestPaths, int myIndex, int timeLeft);

int main() {
    string name;
    string leadTo;
    string junk;
    // Need to keep track of names until we get the whole name->index map figured out
    vector<vector<string>> tempPaths;
    unordered_map<string, int> nameToIndex;
    int count = 0;
    int currentPos;
    vector<int> flowRates;
    vector<vector<bool>> map;

    // Go until end of input
    while (cin >> junk) { // Valve
        cin >> name;
        if (name == "AA") {
            currentPos = count;
        }
        nameToIndex.insert_or_assign(name, count);
        cin >> junk >> junk >> junk; // has flow rate={NUM};
        flowRates.push_back(stoi(junk.substr(5, junk.length() - 6))); // Flow Rate parsed
        
        cin >> junk >> junk >> junk >> junk; // Tunnels lead to valves

        // Parse the paths
        tempPaths.push_back(vector<string>());
        while ((cin >> leadTo)) {
            bool shouldBreak = false;
            if (leadTo[leadTo.length() - 1] != ',') {
                // The last one of the line
                shouldBreak = true;
            } else {
                // There's more, but we need to get rid of the comma
                leadTo = leadTo.substr(0, leadTo.length() - 1);
            }
            tempPaths[count].push_back(leadTo);

            if (shouldBreak) {
                break;
            }
        }

        count++;
    }

    // Build the map for real
    for (int i = 0; i < count; i++) {
        map.push_back(vector<bool>(count, false));
        for (int j = 0; j < tempPaths[i].size(); j++) {
            int foundIndex = nameToIndex[tempPaths[i][j]];
            map[i][foundIndex] = true;
        }
    }
    vector<vector<int>> shortestPaths(map.size(), vector<int>(map.size(), map.size() + 1));
    // We could also use a matrix of what the shortest paths from each node to each other node are
    for (int i = 0; i < map.size(); i++) {
        // Idea is to find the shortest paths from this node to each other node
        queue<int> indexes;
        indexes.push(i);
        shortestPaths[i][i] = 0; // No distance to get to myself
        while (!indexes.empty()) {
            int toCheck = indexes.front();
            indexes.pop();
            for (int j = 0; j < map[toCheck].size(); j++) {
                if (map[toCheck][j] && (shortestPaths[i][j] > shortestPaths[i][toCheck] + 1)) {
                    // Can get here from this node
                    shortestPaths[i][j] = shortestPaths[i][toCheck] + 1;
                    indexes.push(j);
                }
            }
        }
    }
    
    cout << maxPressure(flowRates, shortestPaths, currentPos, 30) << endl;

    return 0;
}

// Optimizations:
//   Do not double back if we didn't open the current valve (waste of time)

int maxPressure(vector<int>& flowRates, vector<vector<int>>& shortestPaths, int myIndex, int timeLeft) {
    int maxFlow = 0;

    // We assume the valve now has already been turned. Our goal is to DFS turning other valves
    for (int i = 0; i < flowRates.size(); i++) {
        if (flowRates[i] > 0) {
            if ((timeLeft - shortestPaths[myIndex][i] - 1) * flowRates[i] > 0) {
                // There is some gain from turning this valve. Do so
                int thisGain = (timeLeft - shortestPaths[myIndex][i] - 1) * flowRates[i];
                vector<int> newFlowRates(flowRates);
                newFlowRates[i] = 0;
                maxFlow = max(maxFlow, thisGain + maxPressure(newFlowRates, shortestPaths, i, timeLeft - (shortestPaths[myIndex][i] + 1)));
            }
        }
    }
 
    return maxFlow;
}