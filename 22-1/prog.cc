#include <iostream>
#include <vector>
#include <string>

enum Space {
    Empty,
    Available,
    Blocked
};

enum Direction {
    Right = 0, 
    Down = 1,
    Left = 2,
    Up = 3
};

using namespace std;

int main() {
    vector<vector<Space>> grid;
    // These will store the index of the first/last non-empty space in each row/column
    vector<int> firstSpaceInRows, firstSpaceInColumns, lastSpaceInRows, lastSpaceInColumns;
    string gridLineToProcess;
    int toMove;
    char dirToTurn;
    Direction curDir = Right;
    int curRow = -1, curColumn = -1;

    // Go until the line break
    while (getline(cin, gridLineToProcess) && gridLineToProcess.length() > 0) {
        grid.push_back(vector<Space>());
        // Will always push a new first/last for the row
        lastSpaceInRows.push_back(gridLineToProcess.size() - 1); // Last character is never empty
        for (int i = 0; i < gridLineToProcess.length(); i++) {
            if (i >= firstSpaceInColumns.size()) {
                firstSpaceInColumns.push_back(-1);
                lastSpaceInColumns.push_back(-1);
            }
            if (gridLineToProcess[i] == '.' || gridLineToProcess[i] == '#') {
                if (gridLineToProcess[i] == '.') {
                    grid[grid.size() - 1].push_back(Available);
                    if (curColumn == -1) {
                        curColumn = i;
                        curRow = grid.size() -1;
                    }
                } else {
                    grid[grid.size() - 1].push_back(Blocked);
                }

                if (firstSpaceInRows.size() != lastSpaceInRows.size()) {
                    // First non-empty space in the row
                    firstSpaceInRows.push_back(i);
                }
                // We always must be lower down than before
                lastSpaceInColumns[i] = grid.size() - 1;

                // If we haven't found a first yet for this column, this must be it
                if (firstSpaceInColumns[i] == -1) {
                    firstSpaceInColumns[i] = grid.size() - 1;
                }
            } else {
                grid[grid.size() - 1].push_back(Empty);
            }
        }
    }
    // Grid parsing is done
    int spaceToCheck;

    while (cin >> toMove) {
        switch (curDir) {
            case Right:
                while (toMove > 0) {
                    // Check if we will go off the grid
                    if (curColumn == grid[curRow].size() - 1 || grid[curRow][curColumn + 1] == Empty) {
                        spaceToCheck = firstSpaceInRows[curRow];
                    } else {
                        spaceToCheck = curColumn + 1;
                    }
                    if (grid[curRow][spaceToCheck] == Blocked) {
                        break;
                    }
                    curColumn = spaceToCheck;
                    toMove--;
                }
                break;

            case Down:
                while (toMove > 0) {
                    // Check if we will go off the grid
                    if (curRow == grid.size() - 1 || curColumn >= grid[curRow + 1].size() || grid[curRow + 1][curColumn] == Empty) {
                        spaceToCheck = firstSpaceInColumns[curColumn];
                    } else {
                        spaceToCheck = curRow + 1;
                    }
                    if (grid[spaceToCheck][curColumn] == Blocked) {
                        break;
                    }
                    curRow = spaceToCheck;
                    toMove--;
                }
                break;

            case Left:
                while (toMove > 0) {
                    // Check if we will go off the grid
                    if (curColumn == 0 || grid[curRow][curColumn - 1] == Empty) {
                        spaceToCheck = lastSpaceInRows[curRow];
                    } else {
                        spaceToCheck = curColumn - 1;
                    }
                    if (grid[curRow][spaceToCheck] == Blocked) {
                        break;
                    }
                    curColumn = spaceToCheck;
                    toMove--;
                }
                break;

            case Up:
                while (toMove > 0) {
                    // Check if we will go off the grid
                    if (curRow == 0 || curColumn >= grid[curRow - 1].size() || grid[curRow - 1][curColumn] == Empty) {
                        spaceToCheck = lastSpaceInColumns[curColumn];
                    } else {
                        spaceToCheck = curRow - 1;
                    }
                    if (grid[spaceToCheck][curColumn] == Blocked) {
                        break;
                    }
                    curRow = spaceToCheck;
                    toMove--;
                }
                break;
        }
        if (cin >> dirToTurn) {
            // Now have to turn
            switch (curDir) {
                case Right:
                    if (dirToTurn == 'R') {
                        curDir = Down;
                    } else {
                        curDir = Up;
                    }
                    break;

                case Down:
                    if (dirToTurn == 'R') {
                        curDir = Left;
                    } else {
                        curDir = Right;
                    }
                    break;

                case Left:
                    if (dirToTurn == 'R') {
                        curDir = Up;
                    } else {
                        curDir = Down;
                    }
                    break;

                case Up:
                    if (dirToTurn == 'R') {
                        curDir = Right;
                    } else {
                        curDir = Left;
                    }
                    break;
            }
        }
    }

    cout << (1000 * (1 + curRow)) + (4 * (1 + curColumn)) + curDir << endl;

    return 0;
}