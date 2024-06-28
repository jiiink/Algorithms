#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Pair;

class Node {
public:
    int f;
    Pair position;
    Node* parent;

    // Custom comparison function to compare Nodes
    bool operator<(const Node& other) const {
        return position < other.position;
    }
};



int main() {
    // Define a set of Nodes
    set<Node> open_set;

    // Insert some Nodes into the set
    Node node1, node2, node3;
    node1.position = make_pair(1, 1);
    node1.f = 10;

    node2.position = make_pair(2, 2);
    node2.f = 20;

    node3.position = make_pair(3, 3);
    node3.f = 30;

    open_set.insert(node1);
    open_set.insert(node2);
    open_set.insert(node3);

    // Define the target Node to search for
    Node target;
    target.position = make_pair(2, 2);
    target.f = 0;

    // Search for the target Node in the set
    auto it = open_set.find(target);

    // Check if the target Node was found
    if (it != open_set.end()) {
        cout << "Item found with f = " << it->f << endl;
    } else {
        cout << "Item not found" << endl;
    }

    return 0;
}
