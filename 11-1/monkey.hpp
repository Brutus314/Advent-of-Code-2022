#ifndef AOC_MONKEY
#define AOC_MONKEY

#include <deque>
#include <utility>
#include <string>

class Monkey {
    private:
        std::deque<long long> _items;
        int _inspectedItems;
        int _test;
        std::size_t _ifTrue;
        std::size_t _ifFalse;
        char _operator;
        std::string _operand;

        long long applyInspection(long long item); // Pesky squaring function means regular unsigned ints aren't big enough

    public:
        Monkey(std::deque<long long> items, int test, std::size_t ifTrue, std::size_t ifFalse, char op, std::string operand);
        std::pair<long long, size_t> inspectNextItem();
        void giveItem(long long item);
        long long getItemsInspected();
};

#endif