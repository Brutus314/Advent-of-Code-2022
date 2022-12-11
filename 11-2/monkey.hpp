#ifndef AOC_MONKEY
#define AOC_MONKEY

#include <deque>
#include <utility>
#include <string>
#include "intInMods.hpp"

class Monkey {
    private:
        std::deque<IntInMods> _items;
        unsigned long long _inspectedItems;
        int _test;
        std::size_t _ifTrue;
        std::size_t _ifFalse;
        char _operator;
        std::string _operand;

        void applyInspection(IntInMods& item); // Pesky squaring function means regular unsigned ints aren't big enough

    public:
        Monkey(std::deque<IntInMods> items, int test, std::size_t ifTrue, std::size_t ifFalse, char op, std::string operand);
        std::pair<IntInMods, size_t> inspectNextItem();
        bool hasItem();
        void giveItem(IntInMods item);
        unsigned long long getItemsInspected();
};

#endif