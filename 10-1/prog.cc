#include <iostream>
#include <string>

using namespace std;

int main() {
    int xReg = 1;
    string command;
    int operand;
    int cyclesProcessed = 0;
    bool processing = true;
    int cyclesWaited = 0;

    int totalSignalStrength = 0;

    // Go until end of input
    while ((cin >> command) && command.length() > 0) {
        // addx takes 2 cycles
        while (processing) {

            if (command == "noop" || cyclesWaited == 1) {
                // noop escapes immediately, and this also catches the second cycle of addx
                cyclesProcessed++;
                processing = false;
            } else if (command == "addx" && cyclesWaited == 0) {
                // Need to start the waiting process
                cin >> operand;
                cyclesProcessed++;
                cyclesWaited = 1;
            }

            // Calculating signal strength can happen in the middle of addx, and happens before addx completes
            if (cyclesProcessed == 20 || cyclesProcessed == 60 || cyclesProcessed == 100 ||
                cyclesProcessed == 140 || cyclesProcessed == 180 || cyclesProcessed == 220) {

                cout << cyclesProcessed << ": " << cyclesProcessed * xReg << endl;
                totalSignalStrength += (cyclesProcessed * xReg);
            }
        }
        // Complete addx
        if (command == "addx") {
            xReg += operand;
        }
        processing = true;
        cyclesWaited = 0;
    }

    cout << totalSignalStrength << endl;
}