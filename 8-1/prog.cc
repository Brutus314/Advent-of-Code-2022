#include <iostream>
#include <string>
#include <vector>

using namespace std;

int visibleTrees(vector<vector<int>> grid);
bool treeVisibleFromUp(vector<vector<int>> grid, int x, int y);
bool treeVisibleFromLeft(vector<vector<int>> grid, int x, int y);
bool treeVisibleFromDown(vector<vector<int>> grid, int x, int y);
bool treeVisibleFromRight(vector<vector<int>> grid, int x, int y);

int main() {
    string input;
    vector<vector<int>> grid;

    // Go until end of input
    while (getline(cin, input) && input.length() > 0) {
        // Create the row and fill it, then add it to the grid
        vector<int> gridRow;

        for (int i = 0; i < input.length(); i++) {
            gridRow.push_back(input[i] - '0');
        }

        grid.push_back(gridRow);
    }

    cout << visibleTrees(grid) << endl;
}

// Keep in mind that the positions of y and x are perhaps a bit backwards
// This is also a slow algorithm (O(yx^2 + xy^2)) but that's an exercise for another day
int visibleTrees(vector<vector<int>> grid) {
    int total = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (treeVisibleFromUp(grid, x, y) || treeVisibleFromLeft(grid, x, y) ||
                treeVisibleFromDown(grid, x, y) || treeVisibleFromRight(grid, x, y)) {
                total++;
            }
        }
    }

    return total;
}

// Logic to be visible from a direction = everything in that direction is shorter
// Up = -y
bool treeVisibleFromUp(vector<vector<int>> grid, int x, int y) {
    for (int i = y - 1; i >= 0; i--) {
        if (grid[i][x] >= grid[y][x]) {
            return false;
        }
    }
    return true;
}

// Left = -x
bool treeVisibleFromLeft(vector<vector<int>> grid, int x, int y) {
    for (int i = x - 1; i >= 0; i--) {
        if (grid[y][i] >= grid[y][x]) {
            return false;
        }
    }
    return true;
}

// Down = +y
bool treeVisibleFromDown(vector<vector<int>> grid, int x, int y) {
    for (int i = y + 1; i < grid.size(); i++) {
        if (grid[i][x] >= grid[y][x]) {
            return false;
        }
    }
    return true;
}

// Right = +x
bool treeVisibleFromRight(vector<vector<int>> grid, int x, int y) {
    for (int i = x + 1; i < grid[0].size(); i++) {
        if (grid[y][i] >= grid[y][x]) {
            return false;
        }
    }
    return true;
}