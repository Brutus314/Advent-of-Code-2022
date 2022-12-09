#include <iostream>
#include <vector>
#include <string>

using namespace std;

int itemPriority(char item);

int main() {
    vector<int> itemsExisting;
    string sack1, sack2, sack3;
    int totalPriority = 0;
    
    // Go until end of input
    while (getline(cin, sack1) && sack1.length() > 0) {
        getline(cin, sack2);
        getline(cin, sack3);
        itemsExisting = vector<int>(52, 0);

        // Check items that exist in sack 1
        for (int i = 0; i < sack1.length(); i++) {
            int priority = itemPriority(sack1[i]);
            if (itemsExisting[priority - 1] == 0) {
                itemsExisting[priority - 1] += 1;
            }
        }

        // Check items that also exist in sack 2
        for (int i = 0; i < sack2.length(); i++) {
            int priority = itemPriority(sack2[i]);
            if (itemsExisting[priority - 1] == 1) {
                itemsExisting[priority - 1] += 1;
            }
        }

        // Find that item that also exists in sack 3
        for (int i = 0; i < sack3.length(); i++) {
            int priority = itemPriority(sack3[i]);
            if (itemsExisting[priority - 1] == 2) {
                totalPriority += priority;
                break;
            }
        }
    }

    cout << totalPriority << endl;

    return 0;
}

int itemPriority(char item) {
    if (item > 'Z') {
        return (item - 'a') + 1;
    } else {
        return (item - 'A') + 27;
    }
}