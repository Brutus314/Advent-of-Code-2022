#include <iostream>
#include <string>
#include <deque>

enum Direction {
    North, 
    South, 
    West,
    East,
    None
};

struct Space {
    public:
        bool hasElf;
        Direction proposedDirection;
        Space() {
            hasElf = false;
            proposedDirection = None;
        }
};

using namespace std;

bool fullCheck(int row, int column, deque<deque<Space*>>& grid);
bool northCheck(int row, int column, deque<deque<Space*>>& grid);
bool southCheck(int row, int column, deque<deque<Space*>>& grid);
bool westCheck(int row, int column, deque<deque<Space*>>& grid);
bool eastCheck(int row, int column, deque<deque<Space*>>& grid);

int main() {
    string input;
    int elfCount = 0;
    deque<deque<Space*>> grid;
    deque<Direction> checkOrder;
    checkOrder.push_back(North);
    checkOrder.push_back(South);
    checkOrder.push_back(West);
    checkOrder.push_back(East);

    // Build initial grid from input
    while (getline(cin, input)) {
        grid.push_back(deque<Space*>());
        for (int i = 0; i < input.length(); i++) {
            grid.back().push_back(new Space());
            if (input[i] == '#') {
                elfCount++;
                grid.back().back()->hasElf = true;
            } else {
                grid.back().back()->hasElf = false;
            }
        }
    }

    // Initial grid built, simulate 10 rounds
    for (int x = 0; x < 10; x++) {
        bool expandRowsUp = false, expandRowsDown = false, expandColumnsLeft = false, expandColumnsRight = false;
        // Figure out proposed moves
        for (int row = 0; row < grid.size(); row++) {
            for (int column = 0; column < grid[row].size(); column++) {
                grid[row][column]->proposedDirection = None;
                if (grid[row][column]->hasElf) {
                    // First check if no one is around
                    if (!fullCheck(row, column, grid)) {
                        for (int d = 0; d < checkOrder.size(); d++) {
                            switch (checkOrder[d]) {
                                case North:
                                    if (northCheck(row, column, grid)) {
                                        grid[row][column]->proposedDirection = North;
                                        if (row == 0) expandRowsUp = true;
                                    }
                                    break;
                                case South:
                                    if (southCheck(row, column, grid)) {
                                        grid[row][column]->proposedDirection = South;
                                        if (row == grid.size() - 1) expandRowsDown = true;
                                    }
                                    break;
                                case West:
                                    if (westCheck(row, column, grid)) {
                                        grid[row][column]->proposedDirection = West;
                                        if (column == 0) expandColumnsLeft = true;
                                    }
                                    break;
                                case East:
                                    if (eastCheck(row, column, grid)) {
                                        grid[row][column]->proposedDirection = East;
                                        if (column == grid[row].size() - 1) expandColumnsRight = true;
                                    }
                                    break;
                                default:
                                    cout << "Error: somehow checking to make None movement" << endl;
                            }
                            if (grid[row][column]->proposedDirection != None) break;
                        }
                    }
                }
            }
        }
        // Prepare the grid in case any elf would go off the board
        if (expandRowsUp) {
            grid.push_front(deque<Space*>(grid.front().size()));
            for (int i = 0; i < grid[0].size(); i++) grid[0][i] = new Space;
        }
        if (expandRowsDown) {
            grid.push_back(deque<Space*>(grid.front().size()));
            for (int i = 0; i < grid[grid.size() - 1].size(); i++) grid[grid.size() - 1][i] = new Space;
        }
        if (expandColumnsLeft) {
            for (int i = 0; i < grid.size(); i++) {
                grid[i].push_front(new Space);
            }
        }
        if (expandColumnsRight) {
            for (int i = 0; i < grid.size(); i++) {
                grid[i].push_back(new Space);
            }
        }

        // Do movements
        for (int row = 0; row < grid.size(); row++) {
            for (int column = 0; column < grid[row].size(); column++) {
                if (grid[row][column]->proposedDirection != None) {
                    switch (grid[row][column]->proposedDirection) {
                        case North:
                            if ((row == 1 || grid[row - 2][column]->proposedDirection != South) && 
                                (column == 0 || grid[row - 1][column - 1]->proposedDirection != East) &&
                                (column == grid[row].size() - 1 || grid[row - 1][column + 1]->proposedDirection != West)) {
                                    // Nothing else planning on moving here, so this elf can move
                                    grid[row][column]->hasElf = false;
                                    grid[row - 1][column]->hasElf = true;
                                }
                            break;
                        case South: 
                            if ((row == grid.size() - 2 || grid[row + 2][column]->proposedDirection != North) && 
                                (column == 0 || grid[row + 1][column - 1]->proposedDirection != East) &&
                                (column == grid[row].size() - 1 || grid[row + 1][column + 1]->proposedDirection != West)) {
                                    // Nothing else planning on moving here, so this elf can move
                                    grid[row][column]->hasElf = false;
                                    grid[row + 1][column]->hasElf = true;
                                }
                            break;
                        case West:
                            if ((column == 1 || grid[row][column - 2]->proposedDirection != East) && 
                                (row == 0 || grid[row - 1][column - 1]->proposedDirection != South) &&
                                (row == grid.size() - 1 || grid[row + 1][column - 1]->proposedDirection != North)) {
                                    // Nothing else planning on moving here, so this elf can move
                                    grid[row][column]->hasElf = false;
                                    grid[row][column - 1]->hasElf = true;
                                }
                            break;
                        case East:
                            if ((column == grid[row].size() - 2 || grid[row][column + 2]->proposedDirection != West) && 
                                (row == 0 || grid[row - 1][column + 1]->proposedDirection != South) &&
                                (row == grid.size() - 1 || grid[row + 1][column + 1]->proposedDirection != North)) {
                                    // Nothing else planning on moving here, so this elf can move
                                    grid[row][column]->hasElf = false;
                                    grid[row][column + 1]->hasElf = true;
                                }
                            break;
                        default:
                            cout << "How did we get here?" << endl;
                    }
                }
            }
        }

        // Cycles which direction is checked first
        checkOrder.push_back(checkOrder.front());
        checkOrder.pop_front();
    }

    cout << (grid.size() * grid[0].size() - elfCount) << endl;

    return 0;
}

bool fullCheck(int row, int column, deque<deque<Space*>>& grid) {
    return northCheck(row, column, grid) && southCheck(row, column, grid) && eastCheck(row, column, grid) && westCheck(row, column, grid);
}

bool northCheck(int row, int column, deque<deque<Space*>>& grid) {
    return (row == 0 || ((column == 0 || !grid[row - 1][column - 1]->hasElf) && // Northwest
            !grid[row - 1][column]->hasElf &&  // North
            (column == grid[row].size() - 1 || !grid[row - 1][column + 1]->hasElf))); // Northeast
}

bool southCheck(int row, int column, deque<deque<Space*>>& grid) {
    return (row == grid.size() - 1 || ((column == 0 || !grid[row + 1][column - 1]->hasElf) && // Southwest
            !grid[row + 1][column]->hasElf &&  // South
            (column == grid[row].size() - 1 || !grid[row + 1][column + 1]->hasElf))); // Southeast
}

bool westCheck(int row, int column, deque<deque<Space*>>& grid) {
    return (column == 0 || ((row == 0 || !grid[row - 1][column - 1]->hasElf) && // Northwest
            !grid[row][column - 1]->hasElf &&  // West
            (row == grid.size() - 1 || !grid[row + 1][column - 1]->hasElf))); // Southwest
}

bool eastCheck(int row, int column, deque<deque<Space*>>& grid) {
    return (column == grid[row].size() - 1 || ((row == 0 || !grid[row - 1][column + 1]->hasElf) && // Northeast
            !grid[row][column + 1]->hasElf &&  // East
            (row == grid.size() - 1 || !grid[row + 1][column + 1]->hasElf))); // Southeast
}