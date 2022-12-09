#include <iostream>

using namespace std;

int calculate(char opponentMove, char myMove);

int main() {
    char opponentMove, myMove;
    int score = 0;
    // Keep going until end of input
    while (cin >> opponentMove) {
        if (cin >> myMove) {
            score += calculate(opponentMove, myMove);
        }
    }
    cout << score << endl;

    return 0;
}

int calculate(char opponentMove, char myMove) {
    switch (myMove) {
        case 'X':
            // I throw rock
            if (opponentMove == 'A') {
                // Opponent throws rock
                return 4;
            } else if (opponentMove == 'C') {
                // Opponent throws paper
                return 7;
            } else {
                // Opponent throws scissors
                return 1;
            }
            break;
        case 'Y':
            // I throw paper
            if (opponentMove == 'B') {
                // Opponent throws paper
                return 5;
            } else if (opponentMove == 'A') {
                // Opponent throws rock
                return 8;
            } else {
                // Opponent throws scissors
                return 2;
            }
            break;
        case 'Z':
            // I throw scissors
            if (opponentMove == 'C') {
                // Opponent throws scissors
                return 6;
            } else if (opponentMove == 'B') {
                // Opponent throws paper
                return 9;
            } else {
                // Opponent throws rock
                return 3;
            }
            break;
        default:
            return 0;
    }
}