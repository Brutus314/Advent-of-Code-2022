#include <iostream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

int main() {
    vector<deque<char>> piles;
    int i, j;
    bool firstTime = true;
    string level;

    // Go until a blank line
    while (getline(cin, level) && level.length() > 0) {
        j = 0;
        // The "image" only has relevant data at every 4th character
        for (i = 1; i < level.length(); i += 4, j++) {
            if (firstTime) {
                piles.push_back(deque<char>());
            }
            // Ignore the "pile description" line
            if (level[i] >= 'A' && level[i] <= 'Z') {
                piles[j].push_front(level[i]);
            }
        }
        firstTime = false;
    }

    string garbage;
    int moveCount, from, to;
    // Finish off the input, a lot of garbage we don't care about
    while (cin >> garbage) { // move
        cin >> moveCount;
        cin >> garbage; // from
        cin >> from;
        cin >> garbage; // to
        cin >> to;

        // Moving x items means x times of taking the top item of one pile and putting it on the other
        for (i = 0; i < moveCount; i++) {
            piles[to - 1].push_back(piles[from - 1].back());
            piles[from - 1].pop_back();
        }
    }

    // What's at the top of each pile
    for (i = 0; i < piles.size(); i++) {
        cout << piles[i].back();
    }

    cout << endl;

    return 0;
}