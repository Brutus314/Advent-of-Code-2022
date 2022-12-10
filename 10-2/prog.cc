#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    int xReg = 1;
    string command;
    int operand;
    int cyclesProcessed = 0;
    bool processing = true;
    int cyclesWaited = 0;

    int totalSignalStrength = 0;

    vector<vector<bool>> pixels(6, vector<bool>(40, false));

    // Go until end of input
    while ((cin >> command) && command.length() > 0) {
        // addx takes 2 cycles
        while (processing) {
            // Drawing happens first, but check for out of bounds just in case
            if (xReg < 40 && cyclesProcessed < 240) {
                if (abs(xReg - (cyclesProcessed % 40)) <= 1) {
                    pixels[cyclesProcessed / 40][cyclesProcessed % 40] = true;
                }
            }

            if (command == "noop" || cyclesWaited >= 1) {
                // noop escapes immediately, and this also catches the second cycle of addx
                cyclesProcessed++;
                processing = false;
            } else if (command == "addx" && cyclesWaited == 0) {
                // Need to start the waiting process
                cin >> operand;
                cyclesProcessed++;
                cyclesWaited = 1;
            }
        }
        // Complete addx
        if (command == "addx") {
            xReg += operand;
        }
        processing = true;
        cyclesWaited = 0;
    }

    // Time to draw the final image
    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            if (pixels[i][j]) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}