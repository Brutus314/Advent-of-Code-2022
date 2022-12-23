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

void getNextSpotOnWrap(int cubeSize, int curRow, int curColumn, Direction dir, int& nextRow, int& nextColumn, Direction& nextDir);

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

    int cubeSize = 999999;
    for (int i = 0; i < lastSpaceInRows.size(); i++) {
        if (((lastSpaceInRows[i] - firstSpaceInRows[i]) + 1) < cubeSize) {
            cubeSize = (lastSpaceInRows[i] - firstSpaceInRows[i]) + 1;
        }
    }

    // Grid parsing is done
    int rowToCheck, columnToCheck;
    Direction nextDir;

    while (cin >> toMove) {
        while (toMove > 0) {
            //cout << "From: " << curRow << ' ' << curColumn << endl;
            switch (curDir) {
                case Right:
                    // Check if we will go off the grid
                    if (curColumn == grid[curRow].size() - 1 || grid[curRow][curColumn + 1] == Empty) {
                        getNextSpotOnWrap(cubeSize, curRow, curColumn, curDir, rowToCheck, columnToCheck, nextDir);
                    } else {
                        columnToCheck = curColumn + 1;
                        rowToCheck = curRow;
                        nextDir = curDir;
                    }
                    if (grid[rowToCheck][columnToCheck] == Blocked) {
                        toMove = 0;
                    } else {
                        //cout << "Next: " << rowToCheck << ' ' << columnToCheck << endl << endl;
                        curColumn = columnToCheck;
                        curRow = rowToCheck;
                        curDir = nextDir;
                        toMove--;
                    }
                    break;

                case Down:
                    // Check if we will go off the grid
                    if (curRow == grid.size() - 1 || curColumn >= grid[curRow + 1].size() || grid[curRow + 1][curColumn] == Empty) {
                        getNextSpotOnWrap(cubeSize, curRow, curColumn, curDir, rowToCheck, columnToCheck, nextDir);
                    } else {
                        columnToCheck = curColumn;
                        rowToCheck = curRow + 1;
                        nextDir = curDir;
                    }
                    if (grid[rowToCheck][columnToCheck] == Blocked) {
                        toMove = 0;
                    } else {
                        // cout << "Next: " << rowToCheck << ' ' << columnToCheck << endl << endl;
                        curColumn = columnToCheck;
                        curRow = rowToCheck;
                        curDir = nextDir;
                        toMove--;
                    }
                    break;

                case Left:
                    // Check if we will go off the grid
                    if (curColumn == 0 || grid[curRow][curColumn - 1] == Empty) {
                        getNextSpotOnWrap(cubeSize, curRow, curColumn, curDir, rowToCheck, columnToCheck, nextDir);
                    } else {
                        columnToCheck = curColumn - 1;
                        rowToCheck = curRow;
                        nextDir = curDir;
                    }
                    if (grid[rowToCheck][columnToCheck] == Blocked) {
                        toMove = 0;
                    } else {
                        //cout << "Next: " << rowToCheck << ' ' << columnToCheck << endl << endl;
                        curColumn = columnToCheck;
                        curRow = rowToCheck;
                        curDir = nextDir;
                        toMove--;
                    }
                    break;

                case Up:
                    // Check if we will go off the grid
                    if (curRow == 0 || curColumn >= grid[curRow - 1].size() || grid[curRow - 1][curColumn] == Empty) {
                        getNextSpotOnWrap(cubeSize, curRow, curColumn, curDir, rowToCheck, columnToCheck, nextDir);
                    } else {
                        columnToCheck = curColumn;
                        rowToCheck = curRow - 1;
                        nextDir = curDir;
                    }
                    if (grid[rowToCheck][columnToCheck] == Blocked) {
                        toMove = 0;
                    } else {
                        //cout << "Next: " << rowToCheck << ' ' << columnToCheck << endl << endl;
                        curColumn = columnToCheck;
                        curRow = rowToCheck;
                        curDir = nextDir;
                        toMove--;
                    }
                    break;
            }
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

// THIS IS HARD CODED TO MY INPUT MAP SHAPE, it doesn't work on the test input
void getNextSpotOnWrap(int cubeSize, int curRow, int curColumn, Direction dir, int& nextRow, int& nextColumn, Direction& nextDir) {
    // Figure out what face we are in
    if (curRow >= cubeSize * 3) {
        // "Back" face
        switch (dir) {
            case Right:
                nextDir = Up;
                nextRow = (cubeSize * 3) - 1;
                nextColumn = cubeSize + (curRow - (cubeSize * 3));
                break;
            case Left:
                nextDir = Down;
                nextRow = 0;
                nextColumn = cubeSize + (curRow - (cubeSize * 3));
                break;
            case Down:
                nextDir = Down;
                nextRow = 0;
                nextColumn = (cubeSize * 2) + curColumn;
                break;
            case Up:
                cout << "Error: Back face facing Up" << endl << endl;
        }
    } else if (curRow >= cubeSize * 2) {
        if (curColumn >= cubeSize) {
            // "Top" face
            switch (dir) {
                case Right:
                    nextDir = Left;
                    nextRow = (cubeSize - 1) - (curRow - (cubeSize * 2));
                    nextColumn = (cubeSize * 3) - 1;
                    break;
                case Left:
                    cout << "Error: Top face facing left" << endl;
                    break;
                case Down:
                    nextDir = Left;
                    nextRow = (cubeSize * 3) + (curColumn - cubeSize);
                    nextColumn = cubeSize - 1;
                    break;
                case Up:
                    cout << "Error: Top face facing Up" << endl;
            }
        } else {
            // "Left" face
            switch (dir) {
                case Right:
                    cout << "Error: Left face facing right" << endl;
                    break;
                case Left:
                    nextDir = Right;
                    nextRow = (cubeSize - 1) - (curRow - (cubeSize * 2));
                    nextColumn = cubeSize;
                    break;
                case Down:
                    cout << "Error: Left face facing Down" << endl;
                    break;
                case Up:
                    nextDir = Right;
                    nextRow = cubeSize + curColumn;
                    nextColumn = cubeSize;
            }
        }
    }
    else if (curRow >= cubeSize) {
        // "Front" face
        switch (dir) {
            case Right:
                nextDir = Up;
                nextRow = cubeSize - 1;
                nextColumn = (cubeSize * 2) + (curRow - cubeSize);
                break;
            case Left:
                nextDir = Down;
                nextRow = cubeSize * 2;
                nextColumn = (cubeSize - 1) - (((cubeSize * 2) - 1) - curRow);
                break;
            case Down:
                cout << "Error: Front face facing Down" << endl;
                break;
            case Up:
                cout << "Error: Front face facing Up" << endl;
        }
    } else {
        if (curColumn >= cubeSize * 2) {
            // "Right" face
            switch (dir) {
                case Right:
                    nextDir = Left;
                    nextRow = (cubeSize * 2) + ((cubeSize - 1) - curRow);
                    nextColumn = (cubeSize * 2) - 1;
                    break;
                case Left:
                    cout << "Error: Right face facing Left" << endl;
                    break;
                case Down:
                    nextDir = Left;
                    nextRow = cubeSize + (curColumn - (cubeSize * 2));
                    nextColumn = (cubeSize * 2) - 1;
                    break;
                case Up:
                    nextDir = Up;
                    nextRow = (cubeSize * 4) - 1;
                    nextColumn = (cubeSize - 1) - (((cubeSize * 3) - 1) - curColumn);
            }
        } else {
            // "Bottom" face
            switch (dir) {
                case Right:
                    cout << "Error: Bottom face facing Right" << endl;
                    break;
                case Left:
                    nextDir = Right;
                    nextRow = (cubeSize * 2) + ((cubeSize - 1) - curRow);
                    nextColumn = 0;
                    break;
                case Down:
                    cout << "Error: Bottom face facing Down" << curRow << " " << curColumn << endl;
                    break;
                case Up:
                    nextDir = Right;
                    nextRow = (cubeSize * 3) + (curColumn - cubeSize);
                    nextColumn = 0;
            }
        }
    }

    //cout << "Next: " << nextRow << ' ' << nextColumn << endl;
    //cout << "From: " << curRow << ' ' << curColumn << endl << endl;
}