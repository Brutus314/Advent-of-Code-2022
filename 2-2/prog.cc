#include <iostream>

using namespace std;

const char LOSE = 'X', DRAW = 'Y', WIN = 'Z';
const char ROCK = 'A', PAPER = 'B', SCISSORS = 'C';

int calculate(char opponentMove, char desiredResult);

int main() {
    char opponentMove, desiredResult;
    int score = 0;
    // Keep going until end of input
    while (cin >> opponentMove) {
        if (cin >> desiredResult) {
            score += calculate(opponentMove, desiredResult);
        }
    }
    cout << score << endl;

    return 0;
}

int calculate(char opponentMove, char desiredResult) {
    switch (desiredResult) {
        case LOSE:
            if (opponentMove == ROCK) {
                // I throw scissors
                return 3;
            } else if (opponentMove == SCISSORS) {
                // I throw paper
                return 2;
            } else if (opponentMove == PAPER) {
                // I throw rock
                return 1;
            } else {
                return 0;
            }
            break;
        case DRAW:
            if (opponentMove == PAPER) {
                // I throw paper
                return 5;
            } else if (opponentMove == ROCK) {
                // I throw rock
                return 4;
            } else if (opponentMove == SCISSORS) {
                // I throw scissors
                return 6;
            } else {
                return 0;
            }
            break;
        case WIN:
            if (opponentMove == SCISSORS) {
                // I throw rock
                return 7;
            } else if (opponentMove == PAPER) {
                // I throw scissors
                return 9;
            } else if (opponentMove == ROCK) {
                // I throw paper
                return 8;
            } else {
                return 0;
            }
            break;
        default:
            return 0;
    }
}