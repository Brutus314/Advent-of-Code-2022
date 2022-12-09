#include <iostream>

using namespace std;

int main() {
    int lowerRange1, upperRange1, lowerRange2, upperRange2;
    int totalOverlapped = 0;

    // Go until end of input
    while (cin >> lowerRange1) {
        // We can ignore a lot of stuff here
        cin.ignore(); // -
        cin >> upperRange1; 
        cin.ignore(); // ,
        cin >> lowerRange2;
        cin.ignore(); // -
        cin >> upperRange2;

        // We don't overlap as long as one minimum is higher than the other's maximum
        if (lowerRange1 <= upperRange2 && lowerRange2 <= upperRange1) {
            totalOverlapped++;
        }
    }

    cout << totalOverlapped << endl;

    return 0;
}