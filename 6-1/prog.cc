#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool stringHasUniqueCharacters(string s);

int main() {
    string input;
    getline(cin, input); // Only 1 line this time!
    int startingOffset;

    // Find where the unique substring is
    for (startingOffset = 0; startingOffset + 4 < input.length(); startingOffset++) {
        if (stringHasUniqueCharacters(input.substr(startingOffset, 4))) {
            break;
        }
    }

    cout << startingOffset + 4 << endl;

    return 0;
}

bool stringHasUniqueCharacters(string s) {
    vector<bool> characters(26, false);
    // To check strings of arbitrary size, would rather just check each existance
    // Return false if a character's existance is seen more than once
    for (int i = 0; i < s.length(); i++) {
        if (characters[s[i] - 'a']) {
            return false;
        } else {
            characters[s[i] - 'a'] = true;
        }
    }
    return true;
}