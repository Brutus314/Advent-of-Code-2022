#include "monkey.hpp"

Monkey::Monkey(std::deque<IntInMods> items, int test, std::size_t ifTrue, std::size_t ifFalse, char op, std::string operand) {
    _items = items;
    _test = test;
    _ifTrue = ifTrue;
    _ifFalse = ifFalse;
    _operator = op;
    _operand = operand;
    _inspectedItems = 0;
}

bool Monkey::hasItem() {
    return _items.size() != 0;
}

std::pair<IntInMods, size_t> Monkey::inspectNextItem() {
    // Get item, inspect it, return new worry level and which monkey gets the item, and remove it from my list
    _inspectedItems++;
    IntInMods itemToInspect = _items[0];
    _items.pop_front();
    applyInspection(itemToInspect);

    // All tests were divisibility tests
    if (itemToInspect.isDivisibleBy(_test)) {
        return std::make_pair(itemToInspect, _ifTrue);
    } else {
        return std::make_pair(itemToInspect, _ifFalse);
    }
}

void Monkey::giveItem(IntInMods item) {
    _items.push_back(item);
}

unsigned long long Monkey::getItemsInspected() {
    return _inspectedItems;
}

void Monkey::applyInspection(IntInMods& item) {
    // Apply operation
    int operand;
    if (_operand == "old") {
        item.squareMyself();
        return;
    } else {
        // Assume integer
        operand = stoi(_operand);
    }

    if (_operator == '*') {
        item = item * operand;
    } else {
        // Assume +
        item = item + operand;
    }
}