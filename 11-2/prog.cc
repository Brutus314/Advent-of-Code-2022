#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include "monkey.hpp"
#include "intInMods.hpp"

using namespace std;

int main() {
    string junk;
    vector<Monkey> monkeys;
    long long item;
    char op;
    int test;
    size_t ifTrue, ifFalse;
    string operand;
    deque<IntInMods> items;

    // Go until end of input. Initial lines are always useless since monkeys are in order
    while (getline(cin, junk)) {
        if (junk.length() == 0) {
            continue;
        }
        items = deque<IntInMods>();
        cin >> junk >> junk; // Starting items: is junk
        // Get the comma-delimitted list
        while (true) {
            cin >> item;
            items.push_back(IntInMods(item));
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

    std::pair<IntInMods, size_t> results = make_pair(0, 0);

    // Simulate 10000 rounds
    for (int i = 0; i < 10000; i++) {
        // In each round, each monkey will inspect each item in sequence, then throw it to another monkey
        for (int j = 0; j < monkeys.size(); j++) {
            while (true) {
                if (!monkeys[j].hasItem()) break; // Monkey has no items left

                results = monkeys[j].inspectNextItem();
                monkeys[results.second].giveItem(results.first);
            }
        }
    }
    // Find the top 2 inspections
    unsigned long long max1 = 0, max2 = 0;
    for (int i = 0; i < monkeys.size(); i++) {
        unsigned long long itemsInsepcted = monkeys[i].getItemsInspected();
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