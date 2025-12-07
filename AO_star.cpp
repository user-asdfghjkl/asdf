/*
       (A, h=7)
       /     \
      OR       OR
     /           \
   (B, h=6)      (C, h=2)
    |   \            |
   AND    OR          OR
   |       \          |
(D, h=1)   (C, h=2)  (E, h=0)
    |                   |
    OR                  Goal
    |                     
   (E, h=0)            

*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Node structure
struct Node {
    string name;
    double h;                // heuristic
    bool solved = false;     // true if solved
    vector< vector< pair<int, double> > > successors; // indices instead of pointers
};

// AO* function using indices
void AOStar(int index, vector<Node>& nodes) {
    Node& node = nodes[index];
    if(node.solved) return;

    double minCost = 1e9;
    vector<int> bestOption;

    // Check all OR options
    for(int i = 0; i < node.successors.size(); i++) {
        vector<pair<int,double>> option = node.successors[i];
        double cost = 0;

        for(int j = 0; j < option.size(); j++) {
            int childIndex = option[j].first;
            double edgeCost = option[j].second;
            cost += edgeCost + nodes[childIndex].h; // edge + child heuristic
        }

        if(cost < minCost) {
            minCost = cost;
            bestOption.clear();
            for(int j = 0; j < option.size(); j++) {
                bestOption.push_back(option[j].first);
            }
        }
    }

    node.h = minCost;      // update heuristic
    node.solved = true;

    // Print node and its best option
    cout << node.name << " -> ";
    for(int i = 0; i < bestOption.size(); i++) {
        cout << nodes[bestOption[i]].name << " ";
    }
    cout << "(Cost=" << node.h << ")\n";

    // Recursively solve children
    for(int i = 0; i < bestOption.size(); i++) AOStar(bestOption[i], nodes);
}

int main() {
    vector<Node> nodes(5);
    nodes[0] = {"A",7};
    nodes[1] = {"B",6};
    nodes[2] = {"C",2};
    nodes[3] = {"D",1};
    nodes[4] = {"E",0};

    // Define successors using indices
    // Format: successors[OR option][AND combination] = {childIndex, edgeCost}
    nodes[0].successors = { {{1,1}}, {{2,4}} };       // A OR B/C
    nodes[1].successors = { {{3,5}}, {{2,2}} };       // B AND D OR C
    nodes[2].successors = { {{4,3}} };                // C OR E
    nodes[3].successors = { {{4,1}} };                // D OR E
    nodes[4].successors = {};                         // Goal

    // Run AO* starting from A (index 0)
    AOStar(0, nodes);

    return 0;
}
