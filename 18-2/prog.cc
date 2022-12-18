#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

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

    // We now essentially have a 3D map here, where everything we marked True is a wall
    // For every "Air" tile, see if it's possible to traverse to the edge
    // An edge is either making it to x/y/z = 0 or x/y/z = DIM_SIZE

    queue<tuple<int, int, int>> toCheck;
    vector<vector<vector<bool>>> canReachEdge(DIM_SIZE, vector<vector<bool>>(DIM_SIZE, vector<bool>(DIM_SIZE, false)));

    // This is horribly inefficient since there's a lot that won't matter, but with this input it's fine
    for (int i = 0; i < DIM_SIZE; i++) {
        for (int j = 0; j < DIM_SIZE; j++) {
            for (int k = 0; k < DIM_SIZE; k++) {
                if (
                    !grid[i][j][k] &&
                    (i == 0 || i == DIM_SIZE - 1 ||
                    j == 0 || j == DIM_SIZE - 1 ||
                    k == 0 || k == DIM_SIZE - 1)
                ) {
                    // there isn't a rock here, and it's on the edge
                    canReachEdge[i][j][k] = true;
                    toCheck.push(make_tuple(i, j, k));
                }
            }
        }
    }
    
    while (!toCheck.empty()) {
        // The idea is that for every tile that can reach the edge, every tile it reaches can also reach the edge
        // Since we start with all edges marked true, anything we can't reach from the initial set must not be able to reach the edge

        int chkX, chkY, chkZ;
        tie(chkX, chkY, chkZ) = toCheck.front();
        toCheck.pop();

        // There are 6 possible paths we can take here, but they must fulfill the following conditions:
        //   We don't go off the edge
        //   That path isn't occupied by rock
        //   That path isn't already verified to be able to reach the edge
        if (chkX != 0 && !grid[chkX - 1][chkY][chkZ] && !canReachEdge[chkX - 1][chkY][chkZ]) {
            canReachEdge[chkX - 1][chkY][chkZ] = true;
            toCheck.push(make_tuple(chkX - 1, chkY, chkZ));
        }
        if (chkX != (DIM_SIZE - 1) && !grid[chkX + 1][chkY][chkZ] && !canReachEdge[chkX + 1][chkY][chkZ]) {
            canReachEdge[chkX + 1][chkY][chkZ] = true;
            toCheck.push(make_tuple(chkX + 1, chkY, chkZ));
        }
        
        if (chkY != 0 && !grid[chkX][chkY - 1][chkZ] && !canReachEdge[chkX][chkY - 1][chkZ]) {
            canReachEdge[chkX][chkY - 1][chkZ] = true;
            toCheck.push(make_tuple(chkX, chkY - 1, chkZ));
        }
        if (chkY != (DIM_SIZE - 1) && !grid[chkX][chkY + 1][chkZ] && !canReachEdge[chkX][chkY + 1][chkZ]) {
            canReachEdge[chkX][chkY + 1][chkZ] = true;
            toCheck.push(make_tuple(chkX, chkY + 1, chkZ));
        }
        
        if (chkZ != 0 && !grid[chkX][chkY][chkZ - 1] && !canReachEdge[chkX][chkY][chkZ - 1]) {
            canReachEdge[chkX][chkY][chkZ - 1] = true;
            toCheck.push(make_tuple(chkX, chkY, chkZ - 1));
        }
        if (chkZ != (DIM_SIZE - 1) && !grid[chkX][chkY][chkZ + 1] && !canReachEdge[chkX][chkY][chkZ + 1]) {
            canReachEdge[chkX][chkY][chkZ + 1] = true;
            toCheck.push(make_tuple(chkX, chkY, chkZ + 1));
        }
    }

    int surfaceArea = 0;

    // A face contributes to surface area if it is not up against another face
    // With the traversal map in our possession, the extra requirement is that that tile must be able to reach the edge
    for (int i = 0; i < DIM_SIZE; i++) {
        for (int j = 0; j < DIM_SIZE; j++) {
            for (int k = 0; k < DIM_SIZE; k++) {
                if (grid[i][j][k]) {
                    if (i == 0 || canReachEdge[i - 1][j][k]) {
                        surfaceArea++;
                    }
                    if (i == (DIM_SIZE - 1) || canReachEdge[i + 1][j][k]) {
                        surfaceArea++;
                    }
                    
                    if (j == 0 || canReachEdge[i][j - 1][k]) {
                        surfaceArea++;
                    }
                    if (j == (DIM_SIZE - 1) || canReachEdge[i][j + 1][k]) {
                        surfaceArea++;
                    }
                    
                    if (k == 0 || canReachEdge[i][j][k - 1]) {
                        surfaceArea++;
                    }
                    if (k == (DIM_SIZE - 1) || canReachEdge[i][j][k + 1]) {
                        surfaceArea++;
                    }
                }
            }
        }
    }

    cout << surfaceArea << endl;
}