#include <iostream>
#include <vector>
using namespace std;

class GraphColoring {
    int n, m;
    vector<vector<int>> adj;
    vector<int> color;

public:
    GraphColoring(int vertices, int colors) {
        n = vertices;
        m = colors;
        adj.resize(n, vector<int>(n, 0));
        color.resize(n, 0);
    }

    void addEdge(int u, int v) {
        adj[u][v] = adj[v][u] = 1;
    }

    bool isSafe(int v, int c) {
        for (int i = 0; i < n; i++)
            if (adj[v][i] && color[i] == c)
                return false;
        return true;
    }

    bool solveColoring(int v) {
        if (v == n) return true;

        for (int c = 1; c <= m; c++) {
            if (isSafe(v, c)) {
                color[v] = c;
                if (solveColoring(v + 1)) return true;
                color[v] = 0;
            }
        }
        return false;
    }

    void printSolution() {
        cout << "Color assignment:\n";
        for (int i = 0; i < n; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
    }
};

int main() {
    GraphColoring g(4, 3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 3);

    if (g.solveColoring(0))
        g.printSolution();
    else
        cout << "No solution found.\n";

    return 0;
}