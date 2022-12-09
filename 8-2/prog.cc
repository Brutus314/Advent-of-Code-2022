#include <iostream>
#include <string>
#include <vector>

using namespace std;

int bestScenicScore(vector<vector<int>> grid);
int treesVisibleToUp(vector<vector<int>> grid, int x, int y);
int treesVisibleToLeft(vector<vector<int>> grid, int x, int y);
int treesVisibleToDown(vector<vector<int>> grid, int x, int y);
int treesVisibleToRight(vector<vector<int>> grid, int x, int y);

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

    cout << bestScenicScore(grid) << endl;
}

// Keep in mind that the positions of y and x are perhaps a bit backwards
// This is also a slow algorithm (O(yx^2 + xy^2)) but that's an exercise for another day
int bestScenicScore(vector<vector<int>> grid) {
    int maxScenicScore = 0;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            int scenicScore = treesVisibleToUp(grid, x, y) * treesVisibleToLeft(grid, x, y) * 
                treesVisibleToDown(grid, x, y) * treesVisibleToRight(grid, x, y);
            
            if (scenicScore > maxScenicScore) {
                maxScenicScore = scenicScore;
            }
        }
    }

    return maxScenicScore;
}

// Visible trees = all trees up to and including one that is the same height or taller
// Up = -y
int treesVisibleToUp(vector<vector<int>> grid, int x, int y) {
    int treesVisible = 0;
    for (int i = y - 1; i >= 0; i--) {
        treesVisible++;
        if (grid[i][x] >= grid[y][x]) {
            break;
        }
    }
    return treesVisible;
}

// Left = -x
int treesVisibleToLeft(vector<vector<int>> grid, int x, int y) {
    int treesVisible = 0;
    for (int i = x - 1; i >= 0; i--) {
        treesVisible++;
        if (grid[y][i] >= grid[y][x]) {
            break;
        }
    }
    return treesVisible;
}

// Down = +y
int treesVisibleToDown(vector<vector<int>> grid, int x, int y) {
    int treesVisible = 0;
    for (int i = y + 1; i < grid.size(); i++) {
        treesVisible++;
        if (grid[i][x] >= grid[y][x]) {
            break;
        }
    }
    return treesVisible;
}

// Right = +x
int treesVisibleToRight(vector<vector<int>> grid, int x, int y) {
    int treesVisible = 0;
    for (int i = x + 1; i < grid[0].size(); i++) {
        treesVisible++;
        if (grid[y][i] >= grid[y][x]) {
            break;
        }
    }
    return treesVisible;
}