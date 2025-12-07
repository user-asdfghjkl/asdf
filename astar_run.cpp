/*
       (A, h=7)
       /     \
   1 /         \ 4
     /           \
(B, h=6)---2---(C, h=2)
   |               |
 5 |               | 3
   |               |
(D, h=1)---1---(E, h=0) <-- Goal

*/


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int v;
    double g; // cost so far
    double f; // g + h
    bool operator>(const Node& o) const { return f > o.f; }
};

void Astar(vector<vector<pair<int,int>>>& adj, vector<int>& h, int start, int goal) {
    int n = adj.size();
    vector<int> parent(n, -1);
    vector<double> g(n, 1e9);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    g[start] = 0;
    pq.push(Node{start, 0.0, static_cast<double>(h[start])});

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        if(cur.v == goal) break;

        for(int i = 0; i < adj[cur.v].size(); i++) {
            int v = adj[cur.v][i].first;
            int w = adj[cur.v][i].second;
            if(g[v] > g[cur.v] + w) {
                g[v] = g[cur.v] + w;
                parent[v] = cur.v;
                pq.push(Node{v, g[v], g[v] + static_cast<double>(h[v])});
            }
        }
    }

    cout << "A* Path: ";
    vector<char> path;
    for(int v = goal; v != -1; v = parent[v]) {
        path.push_back('A' + v);
        if(v == start) break;
    }
    reverse(path.begin(), path.end());
    for(char node : path){
        cout << node << " ";
    }
    cout << "Cost=" << g[goal] << "\n";
}

int main() {
    vector<vector<pair<int,int>>> adjw = {
        {{1,1},{2,4}},       // A
        {{0,1},{2,2},{3,5}}, // B
        {{0,4},{1,2},{4,3}}, // C
        {{1,5},{4,1}},       // D
        {{2,3},{3,1}}        // E
    };

    vector<int> h = {7,6,2,1,0};

    int start = 0, goal = 4; // A -> E
    Astar(adjw, h, start, goal);
}