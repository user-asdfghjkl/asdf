#include <iostream>
using namespace std;

int adj[10][10];
int color[10];
int n, m;

bool safe(int v, int c) {
    for (int i = 1; i <= n; i++)
        if (adj[v][i] == 1 && color[i] == c)
            return false;
    return true;
}

bool solve(int v) {
    if (v > n) return true;

    for (int c = 1; c <= m; c++) {
        if (safe(v, c)) {
            color[v] = c;
            if (solve(v + 1)) return true;
            color[v] = 0;  // backtracking
        }
    }
    return false;
}

int main() {
    n = 4;  
    m = 3;  // red, green, blue

    // Square edges
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;
    adj[3][4] = adj[4][3] = 1;
    adj[4][1] = adj[1][4] = 1;

    if (solve(1)) {
        cout << "Coloring:\n";
        for (int i = 1; i <= n; i++) {
            if (color[i] == 1) cout << i << " -> Red\n";
            if (color[i] == 2) cout << i << " -> Green\n";
            if (color[i] == 3) cout << i << " -> Blue\n";
        }
    } else {
        cout << "No solution\n";
    }
}
