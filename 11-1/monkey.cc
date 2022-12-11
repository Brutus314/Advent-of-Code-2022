#include "monkey.hpp"

Monkey::Monkey(std::deque<long long> items, int test, std::size_t ifTrue, std::size_t ifFalse, char op, std::string operand) {
    _items = items;
    _test = test;
    _ifTrue = ifTrue;
    _ifFalse = ifFalse;
    _operator = op;
    _operand = operand;
    _inspectedItems = 0;
}

std::pair<long long, size_t> Monkey::inspectNextItem() {
    // Get item, inspect it, return new worry level and which monkey gets the item, and remove it from my list
    if (_items.size() == 0) return std::make_pair(-1, 0);

    _inspectedItems++;
    long long itemToInspect = _items[0];
    _items.pop_front();
    long long newWorryLevel = applyInspection(itemToInspect);

    // All tests were divisibility tests
    if (newWorryLevel % _test == 0) {
        return std::make_pair(newWorryLevel, _ifTrue);
    } else {
        return std::make_pair(newWorryLevel, _ifFalse);
    }
}

void Monkey::giveItem(long long item) {
    _items.push_back(item);
}

long long Monkey::getItemsInspected() {
    return _inspectedItems;
}

long long Monkey::applyInspection(long long item) {
    // Apply operation, divide by 3
    long long operand;
    if (_operand == "old") {
        operand = item;
    } else {
        // Assume integer
        operand = stoi(_operand);
    }

    if (_operator == '*') {
        return (item * operand) / 3;
    } else {
        // Assume +
        return (item + operand) / 3;
    }
}