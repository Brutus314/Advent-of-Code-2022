#include <iostream>
#include <vector>

struct Node {
    public:
        int value;
        Node* last;
        Node* next;

        Node(int v) {
            value = v;
            last = NULL;
            next = NULL;
        }
};

using namespace std;

void swapNodes(Node* first, Node* second);

int main() {
    vector<Node*> nodes; // Stores the order to mix
    Node* zero = NULL;
    int value;

    // Go until end of input
    while (cin >> value) {
        // Wow, no junk this time!
        Node* tmp = new Node(value);
        if (nodes.size() != 0) {
            // We can wire some pointers
            nodes[nodes.size() - 1]->next = tmp;
            tmp->last = nodes[nodes.size() - 1];
        }
        nodes.push_back(tmp);
        if (value == 0) {
            // We need to keep extra eyes on this one
            zero = tmp;
        }
    }

    // Need to close the nodes
    nodes[0]->last = nodes[nodes.size() - 1];
    nodes[nodes.size() - 1]->next = nodes[0];

    // Do the mixing
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->value < 0) {
            int swaps = nodes[i]->value * -1;
            swaps = swaps % (nodes.size() - 1);
            for (int j = 0; j < swaps; j++) {
                swapNodes(nodes[i]->last, nodes[i]);
            }
        } else {
            int swaps = nodes[i]->value;
            swaps = swaps % (nodes.size() - 1);
            for (int j = 0; j < swaps; j++) {
                swapNodes(nodes[i], nodes[i]->next);
            }
        }
    }

    int valueToTraverse = 1000 % (nodes.size());
    int total = 0;
    Node* currentNode = zero;
    for (int x = 0; x < 3; x++) {
        for (int i = 0; i < valueToTraverse; i++) {
            currentNode = currentNode->next;
        }
        total += currentNode->value;
    }

    cout << total << endl;

    return 0;
}

void swapNodes(Node* first, Node* second) {
    if (first->next == NULL || first->next == first->last) {
        // Shouldn't happen with our input, but this means it's a 1-or-2-length list and swapping is useless
        return;
    }
    first->last->next = second;
    second->next->last = first;

    first->next = second->next;
    second->last = first->last;

    first->last = second;
    second->next = first;
}