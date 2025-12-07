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

/*
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
    pq.push(Node{
        start, 0.0, static_cast<double>(h[start])
        }
    );

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
    for(char node : path) cout << node << " ";
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
*/
//8 puzzle game

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> state;
    int g, h, f;
    vector<string> path;
    bool operator>(const Node& other) const { return f > other.f; }
};

string stateToString(vector<int>& state) {
    string s = "";
    for (int x : state) s += to_string(x);
    return s;
}

int manhattan(vector<int>& state, vector<int>& goal) {
    int dist = 0;
    for (int i = 0; i < 9; i++) {
        if (state[i] == 0) continue;
        int x1 = i / 3, y1 = i % 3;
        int pos = find(goal.begin(), goal.end(), state[i]) - goal.begin();
        int x2 = pos / 3, y2 = pos % 3;
        dist += abs(x1 - x2) + abs(y1 - y2);
    }
    return dist;
}

vector<vector<int>> getMoves(vector<int>& state) {
    vector<vector<int>> moves;
    int pos = find(state.begin(), state.end(), 0) - state.begin();
    int row = pos / 3, col = pos % 3;
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};

    for (int i = 0; i < 4; i++) {
        int newRow = row + dx[i], newCol = col + dy[i];
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            int newPos = newRow*3 + newCol;
            swap(state[pos], state[newPos]);
            moves.push_back(state);
            swap(state[pos], state[newPos]);
        }
    }
    return moves;
}

bool solveAstar(vector<int> start, vector<int> goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<string> visited;
    pq.push({start,0,manhattan(start,goal),manhattan(start,goal),{}});
    visited.insert(stateToString(start));

    string directions[4] = {"Up","Down","Left","Right"};
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        if(cur.state == goal) {
            cout << "Solved in " << cur.g << " moves.\nPath:\n";
            for(auto s: cur.path) cout << s << "\n";
            return true;
        }

        int pos = find(cur.state.begin(), cur.state.end(), 0) - cur.state.begin();
        int row = pos/3, col = pos%3;

        for(int i=0;i<4;i++){
            int newRow = row + dx[i], newCol = col + dy[i];
            if(newRow<0||newRow>=3||newCol<0||newCol>=3) continue;

            vector<int> next = cur.state;
            swap(next[row*3+col], next[newRow*3+newCol]);
            string s = stateToString(next);
            if(visited.find(s)==visited.end()){
                visited.insert(s);
                Node nextNode;
                nextNode.state = next;
                nextNode.g = cur.g + 1;
                nextNode.h = manhattan(next, goal);
                nextNode.f = nextNode.g + nextNode.h;
                nextNode.path = cur.path;
                nextNode.path.push_back(directions[i]);
                pq.push(nextNode);
            }
        }
    }
    cout << "No solution found.\n";
    return false;
}

void printPuzzle(vector<int>& state){
    for(int i=0;i<9;i++){
        if(state[i]==0) cout<<"  ";
        else cout<<state[i]<<" ";
        if((i+1)%3==0) cout<<"\n";
    }
    cout<<"-------\n";
}

int main() {
    vector<int> start = {1,2,3,4,0,6,7,5,8};
    //vector<int> start = {1,2,3,0,4,6,7,5,8};
    //vector<int> start={8,3,1,6,4,7,0,5,2}; //hard puzzle

    vector<int> goal  = {1,2,3,4,5,6,7,8,0};

    cout<<"Start Puzzle:\n"; printPuzzle(start);
    cout<<"Goal Puzzle:\n"; printPuzzle(goal);

    solveAstar(start, goal);

    return 0;
}

Apply the knowledge and compare two queries below and give your opinion about
accuracy and/or problems if any in the query,

1. SELECT * FROM Users WHERE Name="John Doe" AND Pass="myPass"
2. SELECT * FROM Users WHERE Name=""or""="" AND Pass=""or""=""_
