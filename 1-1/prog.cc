#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<int> list;
    string numStr;
    
    // Keep going until end of input
    while (getline(cin, numStr)) {
        int num = stoi(numStr);

        // Keep summing until an empty line, then add that number
        while(getline(cin, numStr) && numStr.length() > 0) {
            num += stoi(numStr);
        }
        list.push_back(num);
    }

    // Who has the max
    int maxValue = 0;
    for(int i = 0; i < list.size(); i++) {
        if (list[i] > maxValue) {
            maxValue = list[i];
        }
    }

    cout << maxValue << endl;

    return 0;
}