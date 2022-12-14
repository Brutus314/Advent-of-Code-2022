#include <iostream>
#include <vector>
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
    vector<ListOrInt*> allLists;

    int numberInput;
    char charInput;

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
        allLists.push_back(currentList);
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
        allLists.push_back(currentList);
        secondList = currentList;
        currentList = NULL;
        getline(cin, junk);
    }

    // Divider packets
    ListOrInt* packet2 = new ListOrInt(true);
    ListOrInt temp1(true);
    ListOrInt temp2(false);
    temp2.setIntValue(2);
    temp1.addItem(temp2);
    packet2->addItem(temp1);
    allLists.push_back(packet2);
    ListOrInt* packet6 = new ListOrInt(true);
    ListOrInt temp3(true);
    ListOrInt temp4(false);
    temp4.setIntValue(6);
    temp3.addItem(temp4);
    packet6->addItem(temp3);
    allLists.push_back(packet6);

    // I'm punting on this and doing a O(n^2) sort
    for (int i = 0; i < allLists.size(); i++) {
        ListOrInt* min = allLists[i];
        int index = i;
        for (int j = i + 1; j < allLists.size(); j++) {
            if (allLists[j]->compareTo(*(min)) == 1) {
                min = allLists[j];
                index = j;
            }
        }
        // Swap this spot with the min found
        ListOrInt* temp = allLists[i];
        allLists[i] = min;
        allLists[index] = temp;
    }

    // Time to find our divider packets
    int index2, index6;
    for (int i = 0; i < allLists.size(); i++) {
        if (allLists[i]->compareTo(*(packet2)) == 0) {
            index2 = i + 1;
            break;
        }
    }
    for (int i = 0; i < allLists.size(); i++) {
        if (allLists[i]->compareTo(*(packet6)) == 0) {
            index6 = i + 1;
            break;
        }
    }
    
    cout << index2 * index6;

    return 0;
}