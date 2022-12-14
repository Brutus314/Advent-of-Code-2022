#include <iostream>
#include <stack>
#include <string>
#include "listOrInt.hpp"

using namespace std;

int main() {
    string junk;
    stack<ListOrInt*> stackDepth;
    ListOrInt* currentList = NULL;
    ListOrInt* firstList;
    ListOrInt* secondList;

    int numberInput;
    char charInput;
    int index = 1;
    int total = 0;

    // Go until end of input
    while (!cin.eof()) {
        // Get first set
        while (true) {
            charInput = cin.peek();
            if (charInput == '[') {
                // New list
                currentList = new ListOrInt(true);
                stackDepth.push(currentList);
                cin.ignore();
            } else if (charInput == ']') {
                // Finish the list
                ListOrInt* temp = currentList;
                stackDepth.pop();
                cin.ignore();
                if (stackDepth.empty()) {
                    // End of the top-level list, must be done
                    getline(cin, junk);
                    break;
                } else {
                    currentList = stackDepth.top();
                    currentList->addItem(*(temp));
                }
            } else if (charInput == ',') {
                // Ignore
                cin.ignore();
                continue;
            } else {
                // Assume it's an integer
                cin >> numberInput;
                ListOrInt intItem(false);
                intItem.setIntValue(numberInput);
                currentList->addItem(intItem);
            }
        }
        firstList = currentList;
        currentList = NULL;
        // Get second set
        while (true) {
            charInput = cin.peek();
            if (charInput == '[') {
                // New list
                currentList = new ListOrInt(true);
                stackDepth.push(currentList);
                cin.ignore();
            } else if (charInput == ']') {
                // Finish the list
                ListOrInt* temp = currentList;
                stackDepth.pop();
                cin.ignore();
                if (stackDepth.empty()) {
                    // End of the top-level list, must be done
                    getline(cin, junk);
                    break;
                } else {
                    currentList = stackDepth.top();
                    currentList->addItem(*(temp));
                }
            } else if (charInput == ',') {
                // Ignore
                cin.ignore();
                continue;
            } else {
                // Assume it's an integer
                cin >> numberInput;
                ListOrInt intItem(false);
                intItem.setIntValue(numberInput);
                currentList->addItem(intItem);
            }
        }
        secondList = currentList;
        currentList = NULL;
        getline(cin, junk);

        if (firstList->compareTo(*(secondList)) != -1) {
            total += index;
        }

        index++;
    }
    cout << total << endl;
    return 0;
}