/*
   (A)
   / \
  1   4
 /     \
(B)---2--(C)
 |        |
 5        3
 |        |
(D)---1--(E)<-- Goal
*/
//Basic Code

/* 
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// ----- BFS -----
void BFS(vector<vector<int>>& adj, int start, int goal) {
    queue<int> q;
    vector<int> parent(adj.size(), -1), vis(adj.size(), 0);
    q.push(start); vis[start] = 1;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u == goal) break;
        for(int v : adj[u]) if(!vis[v]) {
            vis[v] = 1; parent[v] = u; q.push(v);
        }
    }

    cout << "BFS Path: ";
    vector<char> path;
    for(int v = goal; v != -1; v = parent[v]) {
        path.push_back('A' + v);
        if(v == start) break;
    }
    reverse(path.begin(), path.end());
    for(char node : path) cout << node << " ";
    cout << "\n";
}

// ----- DFS -----
void DFS(vector<vector<int>>& adj, int start, int goal) {
    stack<int> st;
    vector<int> parent(adj.size(), -1), vis(adj.size(), 0);
    st.push(start); vis[start] = 1;

    while(!st.empty()) {
        int u = st.top(); st.pop();
        if(u == goal) break;
        for(int v : adj[u]) if(!vis[v]) {
            vis[v] = 1; parent[v] = u; st.push(v);
        }
    }

    cout << "DFS Path: ";
    vector<char> path;
    for(int v = goal; v != -1; v = parent[v]) {
        path.push_back('A' + v);
        if(v == start) break;
    }
    reverse(path.begin(), path.end());
    for(char node : path) cout << node << " ";
    cout << "\n";
}

int main() {
    // Unweighted graph (for BFS, DFS)
    vector<vector<int>> adj = {
        {1,2}, {0,2,3}, {0,1,4}, {1,4}, {2,3}
    };

    int start = 0, goal = 4; // A -> E
    BFS(adj, start, goal);
    DFS(adj, start, goal);
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

// Print the puzzle state
void printPuzzle(vector<int>& state) {
    for(int i = 0; i < 9; i++) {
        if(state[i] == 0) cout << "  ";
        else cout << state[i] << " ";
        if((i + 1) % 3 == 0) cout << "\n";
    }
    cout << "-------\n";
}

// Get possible moves from current state
vector<vector<int>> getMoves(vector<int> state) {
    vector<vector<int>> moves;
    int pos = find(state.begin(), state.end(), 0) - state.begin();
    int row = pos / 3, col = pos % 3;
    
    // Up, Down, Left, Right moves
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for(int i = 0; i < 4; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        
        if(newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            int newPos = newRow * 3 + newCol;
            swap(state[pos], state[newPos]);
            moves.push_back(state);
            swap(state[pos], state[newPos]); // swap back
        }
    }
    return moves;
}

// Convert state to string for comparison
string stateToString(vector<int>& state) {
    string s = "";
    for(int x : state) s += to_string(x);
    return s;
}

// BFS to solve puzzle
bool solveBFS(vector<int> start, vector<int> goal) {
    queue<pair<vector<int>, int>> q;
    set<string> visited;
    
    q.push({start, 0});
    visited.insert(stateToString(start));
    
    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        
        vector<int> state = curr.first;
        int steps = curr.second;
        
        if(state == goal) {
            cout << "BFS: Solved in " << steps << " steps!\n";
            cout << "BFS explored " << visited.size() << " states\n\n";
            return true;
        }
        
        if(steps > 12) continue; // limit depth
        
        vector<vector<int>> nextMoves = getMoves(state);
        for(auto move : nextMoves) {
            string moveStr = stateToString(move);
            if(visited.find(moveStr) == visited.end()) {
                visited.insert(moveStr);
                q.push({move, steps + 1});
            }
        }
    }
    
    cout << "BFS: No solution found!\n\n";
    return false;
}

// DFS to solve puzzle
bool solveDFS(vector<int> start, vector<int> goal) {
    stack<pair<vector<int>, int>> st;
    set<string> visited;
    
    st.push({start, 0});
    visited.insert(stateToString(start));
    
    while(!st.empty()) {
        auto curr = st.top();
        st.pop();
        
        vector<int> state = curr.first;
        int steps = curr.second;
        
        if(state == goal) {
            cout << "DFS: Solved in " << steps << " steps!\n";
            cout << "DFS explored " << visited.size() << " states\n\n";
            return true;
        }
        
        if(steps > 12) continue; // limit depth
        
        vector<vector<int>> nextMoves = getMoves(state);
        for(auto move : nextMoves) {
            string moveStr = stateToString(move);
            if(visited.find(moveStr) == visited.end()) {
                visited.insert(moveStr);
                st.push({move, steps + 1});
            }
        }
    }
    
    cout << "DFS: No solution found!\n\n";
    return false;
}

int main() {
    // Initial puzzle state (0 represents empty space)
    vector<int> start = {1, 2, 3, 4, 0, 6, 7, 5, 8};
    
    // Goal state
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    
    cout << "8-Puzzle Solver - BFS vs DFS Comparison\n";
    cout << "======================================\n";
    
    cout << "Starting puzzle:\n";
    printPuzzle(start);
    
    cout << "Goal puzzle:\n";
    printPuzzle(goal);
    
    cout << "\nSolving with BFS:\n";
    cout << "-----------------\n";
    solveBFS(start, goal);
    
    cout << "Solving with DFS:\n";
    cout << "-----------------\n";
    solveDFS(start, goal);
    
    cout << "Comparison:\n";
    cout << "- BFS finds shortest path (optimal solution)\n";
    cout << "- DFS may find longer path but uses less memory\n";
    cout << "- Both use similar logic to your graph code!\n";
    
    return 0;
}