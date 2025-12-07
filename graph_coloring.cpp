#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using namespace std;

bool isSafe(int node, int color, vector<int>& colors, vector<vector<int>>& graph) {
    for (int adj : graph[node]) {
        if (colors[adj] == color) return false; // neighbor has same color
    }
    return true;
}

bool solve(int node, int m, vector<int>& colors, vector<vector<int>>& graph) {
    int n = graph.size();
    if (node == n) return true; // all nodes colored

    for (int c = 0; c < m; c++) {
        if (isSafe(node, c, colors, graph)) {
            colors[node] = c;
            if (solve(node + 1, m, colors, graph)) return true;
            colors[node] = -1; // backtrack
        }
    }
    return false;
}

int main() {
    // Graph: Square (Cycle of 4)
    int n = 4;
    vector<vector<int>> graph = {
        {1,3},  // A connected to B, D
        {0,2},  // B connected to A, C
        {1,3},  // C connected to B, D
        {0,2}   // D connected to A, C
    };

    vector<string> nodeNames = {"A","B","C","D"};
    vector<string> colorNames = {"Red","Green","Blue"};

    cout << "Graph (Square):\n";
    cout << "   (A)---(B)\n";
    cout << "    |     |\n";
    cout << "    |     |\n";
    cout << "   (D)---(C)\n\n";

    int m = 3; // number of colors allowed
    vector<int> colors(n, -1);

    if (solve(0, m, colors, graph)) {
        cout << "Coloring Solution (using up to " << m << " colors):\n";
        for (int i = 0; i < n; i++) {
            cout << nodeNames[i] << " -> " << colorNames[colors[i]] << "\n";
        }
    } else {
        cout << "No solution with " << m << " colors.\n";
    }

    return 0;
}
