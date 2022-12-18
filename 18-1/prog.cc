#include <iostream>
#include <vector>

using namespace std;

const int DIM_SIZE = 20;

int main() {
    int x, y, z;
    vector<vector<vector<bool>>> grid(DIM_SIZE, vector<vector<bool>>(DIM_SIZE, vector<bool>(DIM_SIZE, false)));

    // Go until end of input to build the grid
    while (cin >> x) {
        cin.ignore(); // comma
        cin >> y;
        cin.ignore(); // comma
        cin >> z;
        
        grid[x][y][z] = true;
    }

    int surfaceArea = 0;

    // A face contributes to surface area if it is not up against another face
    for (int i = 0; i < DIM_SIZE; i++) {
        for (int j = 0; j < DIM_SIZE; j++) {
            for (int k = 0; k < DIM_SIZE; k++) {
                if (grid[i][j][k]) {
                    if (i == 0 || !grid[i - 1][j][k]) {
                        surfaceArea++;
                    }
                    if (i == (DIM_SIZE - 1) || !grid[i + 1][j][k]) {
                        surfaceArea++;
                    }
                    
                    if (j == 0 || !grid[i][j - 1][k]) {
                        surfaceArea++;
                    }
                    if (j == (DIM_SIZE - 1) || !grid[i][j + 1][k]) {
                        surfaceArea++;
                    }
                    
                    if (k == 0 || !grid[i][j][k - 1]) {
                        surfaceArea++;
                    }
                    if (k == (DIM_SIZE - 1) || !grid[i][j][k + 1]) {
                        surfaceArea++;
                    }
                }
            }
        }
    }

    cout << surfaceArea << endl;
}