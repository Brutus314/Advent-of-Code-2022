#include <iostream>
#include <vector>
#include <string>

using namespace std;

int itemPriority(char item);

int main() {
    vector<bool> itemsExisting;
    string items, com1, com2;
    int totalPriority = 0;
    
    // Go until end of input
    while (getline(cin, items)) {
        itemsExisting = vector<bool>(52, false);
        // Compartments broken in even halves
        com1 = items.substr(0, items.length() / 2);
        com2 = items.substr(items.length() / 2);

        // Check for each item's existance
        for (int i = 0; i < com1.length(); i++) {
            itemsExisting[itemPriority(com1[i]) - 1] = true;
        }

        // Check for the item that exists in both
        for (int i = 0; i < com2.length(); i++) {
            int priority = itemPriority(com2[i]);
            if (itemsExisting[priority - 1]) {
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