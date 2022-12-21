#include <iostream>
#include <unordered_map>
#include <string>

enum Operations {
    Add = '+',
    Subtract = '-',
    Multiply = '*',
    Divide = '/'
};

struct Monkey {
    public:
        long long value;
        bool hasValue;
        std::string monkey1;
        std::string monkey2;
        Operations op;

        Monkey() {
            hasValue = false;
        }

        void setValue (long long newValue) {
            hasValue = true;
            value = newValue;
        }
};

using namespace std;

bool stringIsNumeric(string in) {
    for (int i = 0; i < in.length(); i++) {
        if (in[i] < '0' || in[i] > '9') {
            return false;
        }
    }
    return true;
}

long long monkeyValue(string monkeyName, unordered_map<string, Monkey*>& monkeys);

int main() {
    string monkey1, monkey2, monkeyName;
    char op;
    unordered_map<string, Monkey*> monkeys;

    // Go until end of input
    while (cin >> monkeyName) {
        monkeyName = monkeyName.substr(0, monkeyName.size() - 1); // Trim the colon
        cin >> monkey1;

        Monkey* monkey = new Monkey;

        // Might have just a number
        if (stringIsNumeric(monkey1)) {
            monkey->setValue(stoi(monkey1));
        } else {
            cin >> op;
            cin >> monkey2;

            switch (op) {
                case '+':
                    monkey->op = Add;
                    break;
                case '-':
                    monkey->op = Subtract;
                    break;
                case '*':
                    monkey->op = Multiply;
                    break;
                case '/':
                    monkey->op = Divide;
                    break;
            }

            monkey->monkey1 = monkey1;
            monkey->monkey2 = monkey2;
        }

        monkeys.insert_or_assign(monkeyName, monkey);
    }

    cout << monkeyValue("root", monkeys) << endl;

    return 0;
}

long long monkeyValue(string monkeyName, unordered_map<string, Monkey*>& monkeys) {
    Monkey* monkey = monkeys[monkeyName];
    if (monkey->hasValue) {
        return monkey->value;
    }

    long long value1, value2;
    value1 = monkeyValue(monkey->monkey1, monkeys);
    value2 = monkeyValue(monkey->monkey2, monkeys);

    long long result;

    switch (monkey->op) {
        case Add:
            result = value1 + value2;
            break;
        case Subtract:
            result = value1 - value2;
            break;
        case Multiply:
            result = value1 * value2;
            break;
        case Divide:
            result = value1 / value2;
            break;
    }

    monkey->setValue(result);
    return result;
}