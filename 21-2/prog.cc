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

bool setMonkeyValues(string monkeyName, unordered_map<string, Monkey*>& monkeys);
void meetTarget(string monkeyName, long long target, unordered_map<string, Monkey*>& monkeys);

int main() {
    string monkey1, monkey2, monkeyName;
    char op;
    unordered_map<string, Monkey*> monkeys;

    // Go until end of input
    while (cin >> monkeyName) {
        monkeyName = monkeyName.substr(0, monkeyName.size() - 1); // Trim the colon
        cin >> monkey1;

        Monkey* monkey = new Monkey;

        // Skip the human's input
        if (monkeyName != "humn") {
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
        }

        monkeys.insert_or_assign(monkeyName, monkey);
    }

    // We need to set what we can first
    setMonkeyValues("root", monkeys);

    // Since the root is special, we need to start at the immediate human-dependent monkey
    if (!monkeys[monkeys["root"]->monkey1]->hasValue) {
        // First monkey is human-dependent, second monkey has target value
        meetTarget(monkeys["root"]->monkey1, monkeys[monkeys["root"]->monkey2]->value, monkeys);
    } else {
        // Second monkey is human-dependent, first monkey has target value
        meetTarget(monkeys["root"]->monkey2, monkeys[monkeys["root"]->monkey1]->value, monkeys);
    }

    cout << monkeys["humn"]->value << endl;

    return 0;
}

bool setMonkeyValues(string monkeyName, unordered_map<string, Monkey*>& monkeys) {
    if (monkeyName == "humn") {
        // We don't set a value for the human
        return false;
    }
    Monkey* monkey = monkeys[monkeyName];
    if (monkey->hasValue) {
        // Our other base case, this means the monkey is not human-dependent
        return true;
    }
    
    setMonkeyValues(monkey->monkey1, monkeys);
    setMonkeyValues(monkey->monkey2, monkeys);

    if (monkeys[monkey->monkey1]->hasValue && monkeys[monkey->monkey2]->hasValue) {
        // This monkey can calculate its value and is not human-dependent
        long long result;
        long long value1 = monkeys[monkey->monkey1]->value;
        long long value2 = monkeys[monkey->monkey2]->value;

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
        return true;
    } else {
        // One of the dependent monkeys is human-dependent; that makes this one human-dependent too
        return false;
    }
}

void meetTarget(string monkeyName, long long target, unordered_map<string, Monkey*>& monkeys) {
    // For a human-dependent monkey, we have one human-dependent dependency and an independent dependency
    // We also know the target
    // This becomes a "solve for x" situation based on the operation we perform
    // T = target, this is known
    // V = independent value, known

    // Base case for the human
    if (monkeyName == "humn") {
        monkeys[monkeyName]->setValue(target);
        return;
    }
    Monkey* monkey = monkeys[monkeyName];
    string humanDependentMonkey;
    long long knownValue;
    bool firstIsIndependent;

    if (monkeys[monkey->monkey1]->hasValue) {
        // First is the independent monkey
        humanDependentMonkey = monkey->monkey2;
        knownValue = monkeys[monkey->monkey1]->value;
        firstIsIndependent = true;
    } else {
        // Second is the independent monkey
        humanDependentMonkey = monkey->monkey1;
        knownValue = monkeys[monkey->monkey2]->value;
        firstIsIndependent = false;
    }

    // Time to solve for the next target
    switch (monkey->op) {
        case Add:
            // X + V = V + X = T
            // X = T - V
            meetTarget(humanDependentMonkey, target - knownValue, monkeys);
            break;
        case Subtract:
            if (firstIsIndependent) {
                // V - X = T
                // X = V - T
                meetTarget(humanDependentMonkey, knownValue - target, monkeys);
            } else {
                // X - V = T
                // X = T + V
                meetTarget(humanDependentMonkey, target + knownValue, monkeys);
            }
            break;
        case Multiply:
            // X * V = V * X = T
            // X = T / V
            meetTarget(humanDependentMonkey, target / knownValue, monkeys);
            break;
        case Divide:
            if (firstIsIndependent) {
                // V / X = T
                // X = V / T
                meetTarget(humanDependentMonkey, knownValue / target, monkeys);
            } else {
                // X / V = T
                // X = T * V
                meetTarget(humanDependentMonkey, target * knownValue, monkeys);
            }
            break;
    }
}