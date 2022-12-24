#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <numeric>

enum SpaceType {
    Wall, 
    Empty,
    Blizzard
};

enum BlizzardDirection {
    Up,
    Right,
    Down,
    Left
};

struct Space {
    public:
        SpaceType type;
        BlizzardDirection dir;
};

using namespace std;

void blizzardTraversal(vector<vector<Space>>& grid, vector<vector<int>>& bestCaseTimes, vector<vector<vector<int>>>& seenState, int curRow, int curColumn, int curTime, int& bestTime);

int main() {
    string input;
    vector<vector<Space>> grid;

    // Go until end of input
    while (getline(cin, input) && input.length() > 0) {
        grid.push_back(vector<Space>());
        for (int i = 0; i < input.length(); i++) {
            Space newSpace;
            switch (input[i]) {
                case '.':
                    newSpace.type = Empty;
                    break;
                case '#':
                    newSpace.type = Wall;
                    break;
                case '>':
                    newSpace.type = Blizzard;
                    newSpace.dir = Right;
                    break;
                case '<':
                    newSpace.type = Blizzard;
                    newSpace.dir = Left;
                    break;
                case '^':
                    newSpace.type = Blizzard;
                    newSpace.dir = Up;
                    break;
                case 'v':
                    newSpace.type = Blizzard;
                    newSpace.dir = Down;
                    break;
                default:
                    cout << input[i] << " how did this get here?" << endl;
            }
            grid[grid.size() - 1].push_back(newSpace);
        }
    }
    // For optimization purposes, we need a best-case map of spaces to time
    vector<vector<int>> bestCaseTime(grid.size(), vector<int>(grid[0].size(), grid.size() * grid[0].size()));
    bestCaseTime[grid.size() - 1][grid[0].size() - 2] = 0; // Ending space always requires 0 time
    
    queue<pair<int, int>> toCheck;
    toCheck.push(make_pair(grid.size() - 1, grid[0].size() - 2));

    while (!toCheck.empty()) {
        pair<int, int> checkingCoords = toCheck.front();
        toCheck.pop();

        // Check if can move up
        if (checkingCoords.first > 1 && bestCaseTime[checkingCoords.first - 1][checkingCoords.second] > bestCaseTime[checkingCoords.first][checkingCoords.second] + 1) {
            bestCaseTime[checkingCoords.first - 1][checkingCoords.second] = bestCaseTime[checkingCoords.first][checkingCoords.second] + 1;
            toCheck.push(make_pair(checkingCoords.first - 1, checkingCoords.second));
        }

        // Check if can move down
        if (checkingCoords.first < (grid.size() - 2) && bestCaseTime[checkingCoords.first + 1][checkingCoords.second] > bestCaseTime[checkingCoords.first][checkingCoords.second] + 1) {
            bestCaseTime[checkingCoords.first + 1][checkingCoords.second] = bestCaseTime[checkingCoords.first][checkingCoords.second] + 1;
            toCheck.push(make_pair(checkingCoords.first + 1, checkingCoords.second));
        }

        // Check if can move left
        if (checkingCoords.second > 1 && bestCaseTime[checkingCoords.first][checkingCoords.second - 1] > bestCaseTime[checkingCoords.first][checkingCoords.second] + 1) {
            bestCaseTime[checkingCoords.first][checkingCoords.second - 1] = bestCaseTime[checkingCoords.first][checkingCoords.second] + 1;
            toCheck.push(make_pair(checkingCoords.first, checkingCoords.second - 1));
        }

        // Check if can move right
        if (checkingCoords.second > (grid[0].size() - 2) && bestCaseTime[checkingCoords.first][checkingCoords.second + 1] > bestCaseTime[checkingCoords.first][checkingCoords.second] + 1) {
            bestCaseTime[checkingCoords.first][checkingCoords.second + 1] = bestCaseTime[checkingCoords.first][checkingCoords.second] + 1;
            toCheck.push(make_pair(checkingCoords.first, checkingCoords.second + 1));
        }
    }
    // We didn't check the starting point, but it's a static spot. Just update it
    bestCaseTime[0][1] = bestCaseTime[1][1] + 1;

    vector<vector<vector<int>>> reachedInEachState(lcm(grid.size() - 2, grid[0].size() - 2), vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), INT_MAX)));

    // Now it's time to do the actual traversal
    int bestTime = INT_MAX;
    blizzardTraversal(grid, bestCaseTime, reachedInEachState, 0, 1, 0, bestTime);

    cout << bestTime << endl;

    return 0;
}

// Optimizations:
//   Try down and right before waiting
//   Try waiting before left and up
//   Don't simulate the blizzard movements; we can calculate based on time past where each blizzard would be
//   If we have already visited this space in the same blizzard cycle but took longer to reach it, kill the branch
//   If the current time spent + the best-case time from the current spot >= the current best time among all branches, kill this branch
void blizzardTraversal(vector<vector<Space>>& grid, vector<vector<int>>& bestCaseTimes, vector<vector<vector<int>>>& seenState, int curRow, int curColumn, int curTime, int& bestTime) {
    if (curRow == grid.size() - 1 && curColumn == grid[0].size() - 2) {
        // We are at the target spot. Did we do better than the previous time?
        if (curTime < bestTime) {
            bestTime = curTime;
        }
        return;
    }
    
    if (curTime + bestCaseTimes[curRow][curColumn] >= bestTime) {
        // No way we could do better than something we already found
        return;
    }

    if (seenState[curTime % seenState.size()][curRow][curColumn] <= curTime) {
        // Already been in this position
        return;
    } else {
        seenState[curTime % seenState.size()][curRow][curColumn] = curTime;
    }

    // Get which spaces we are looking for a particular blizzard for, keeping wrapping into account
    int blizzardMovingRight = curColumn - (curTime % (grid[curRow].size() - 2));
    if (blizzardMovingRight < 1) blizzardMovingRight += (grid[curRow].size() - 2);

    int blizzardMovingLeft = curColumn + (curTime % (grid[curRow].size() - 2));
    if (blizzardMovingLeft > grid[curRow].size() - 2) blizzardMovingLeft -= (grid[curRow].size() - 2);

    int blizzardMovingDown = curRow - (curTime % (grid.size() - 2));
    if (blizzardMovingDown < 1) blizzardMovingDown += (grid.size() - 2);

    int blizzardMovingUp = curRow + (curTime % (grid.size() - 2));
    if (blizzardMovingUp > grid.size() - 2) blizzardMovingUp -= (grid.size() - 2);

    // See if this is a legal spot
    // Not legal is the original spot of one of our indexes has that type of blizzard
    if (grid[curRow][blizzardMovingRight].type == Blizzard && grid[curRow][blizzardMovingRight].dir == Right) return;
    if (grid[curRow][blizzardMovingLeft].type == Blizzard && grid[curRow][blizzardMovingLeft].dir == Left) return;
    if (grid[blizzardMovingUp][curColumn].type == Blizzard && grid[blizzardMovingUp][curColumn].dir == Up) return;
    if (grid[blizzardMovingDown][curColumn].type == Blizzard && grid[blizzardMovingDown][curColumn].dir == Down) return;

    // Now try moving in each non-wall spot
    if (curRow < grid.size() - 2 || (curRow == grid.size() - 2 && curColumn == grid[curRow].size() - 2)) {
        // Can move down
        // Special case on final row: can only move down if at final column
        blizzardTraversal(grid, bestCaseTimes, seenState, curRow + 1, curColumn, curTime + 1, bestTime);
    }

    if (curColumn < grid[curRow].size() - 2) {
        // Can move right
        blizzardTraversal(grid, bestCaseTimes, seenState, curRow, curColumn + 1, curTime + 1, bestTime);
    }

    // Can wait
    blizzardTraversal(grid, bestCaseTimes, seenState, curRow, curColumn, curTime + 1, bestTime);

    if (curColumn > 1) {
        // Can move left
        blizzardTraversal(grid, bestCaseTimes, seenState, curRow, curColumn - 1, curTime + 1, bestTime);
    }

    if (curRow > 1) {
        // Can move up
        // You might think there is a special case that we can move back to the start, but we could have gotten the same result by just waiting there instead
        blizzardTraversal(grid, bestCaseTimes, seenState, curRow - 1, curColumn, curTime + 1, bestTime);
    }
}