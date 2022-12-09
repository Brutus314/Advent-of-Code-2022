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

    // Which 3 have the max? Keep track of top 3, push down the correct ones as new highest are found
    int maxValue1 = 0;
    int maxValue2 = 0;
    int maxValue3 = 0;

    for(int i = 0; i < list.size(); i++) {
        if (list[i] > maxValue1) {
            maxValue3 = maxValue2;
            maxValue2 = maxValue1;
            maxValue1 = list[i];
        } else if (list[i] > maxValue2) {
            maxValue3 = maxValue2;
            maxValue2 = list[i];
        } else if (list[i] > maxValue3) {
            maxValue3 = list[i];
        }
    }

    cout << maxValue1 << endl << maxValue2 << endl << maxValue3 << endl << endl << (maxValue1 + maxValue2 + maxValue3) << endl;

    return 0;
}