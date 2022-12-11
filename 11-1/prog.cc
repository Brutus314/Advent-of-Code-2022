#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include "monkey.hpp"

using namespace std;

int main() {
    string junk;
    vector<Monkey> monkeys;
    long long item;
    char op;
    int test;
    size_t ifTrue, ifFalse;
    string operand;
    deque<long long> items;

    // Go until end of input. Initial lines are always useless since monkeys are in order
    while (getline(cin, junk)) {
        if (junk.length() == 0) {
            continue;
        }
        items = deque<long long>();
        cin >> junk >> junk; // Starting items: is junk
        // Get the comma-delimitted list
        while (true) {
            cin >> item;
            items.push_back(item);
            if (cin.peek() == ',') cin.ignore();
            else break;
        }

        cin >> junk >> junk >> junk >> junk; // Operation: new = old is junk
        cin >> op >> operand; // Get * or + and the operand to use (may be an integer or "old")

        cin >> junk >> junk >> junk; // Test: divisible by is junk
        cin >> test; // Always a divisble by integer

        cin >> junk >> junk >> junk >> junk >> junk; // If true: throw to monkey is junk
        cin >> ifTrue;

        cin >> junk >> junk >> junk >> junk >> junk; // If false: throw to monkey is junk
        cin >> ifFalse;

        monkeys.push_back(Monkey(items, test, ifTrue, ifFalse, op, operand));
    }

    std::pair<int, size_t> results;

    // Simulate 20 rounds
    for (int i = 0; i < 20; i++) {
        // In each round, each monkey will inspect each item in sequence, then throw it to another monkey
        for (int j = 0; j < monkeys.size(); j++) {
            while (true) {
                results = monkeys[j].inspectNextItem();
                if (results.first == -1) break; // Monkey has no items left

                monkeys[results.second].giveItem(results.first);
            }
        }
    }
    // Find the top 2 inspections
    int max1 = 0, max2 = 0;
    for (int i = 0; i < monkeys.size(); i++) {
        int itemsInsepcted = monkeys[i].getItemsInspected();
        if (itemsInsepcted > max1) {
            max2 = max1;
            max1 = itemsInsepcted;
        } else if (itemsInsepcted > max2) {
            max2 = itemsInsepcted;
        }
    }

    cout << (max1 * max2) << endl;

    return 0;
}