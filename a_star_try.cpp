// “A* Pathfinding Algorithm” in maze
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;
    int g;   // cost so far
    int f;   // g + h
    bool operator>(const Node& other) const { return f > other.f; }
};

int heuristic(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);   // Manhattan distance
}

void AstarGrid(vector<vector<int>>& grid, int sx, int sy, int gx, int gy) {
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, make_pair(-1,-1)));

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[sx][sy] = 0;
    pq.push(Node{sx, sy, 0, heuristic(sx, sy, gx, gy)});

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while(!pq.empty()){
        Node cur = pq.top();
        pq.pop();

        if(cur.x == gx && cur.y == gy)
            break;

        for(int i=0;i<4;i++){
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny]==0){
                int ng = cur.g + 1;

                if(ng < dist[nx][ny]){
                    dist[nx][ny] = ng;

                    parent[nx][ny] = make_pair(cur.x, cur.y);

                    int f = ng + heuristic(nx, ny, gx, gy);
                    pq.push(Node{nx, ny, ng, f});
                }
            }
        }
    }

    // ⭐⭐⭐ SIMPLE PATH PRINTING ⭐⭐⭐
    cout << "Path: ";

    int x = gx, y = gy;
    vector<pair<int,int>> path;

    while(!(x == sx && y == sy)){
        path.push_back(make_pair(x, y));
        pair<int,int> p = parent[x][y];
        x = p.first;
        y = p.second;
    }
    path.push_back(make_pair(sx, sy));

    reverse(path.begin(), path.end());

    for(int i = 0; i < path.size(); i++)
        cout << "(" << path[i].first << "," << path[i].second << ") ";

    cout << "\nCost = " << dist[gx][gy] << endl;
}

int main() {
    vector<vector<int>> grid = {
        {0,0,0},
        {1,0,1},
        {0,0,0}
    };

    AstarGrid(grid, 0, 0, 2, 2);
}

//     vector<vector<int>> grid = {
//     {0,0,0,0,0},
//     {1,0,1,1,0},
//     {0,0,0,0,0},
//     {0,1,1,0,0}
//     };
// AstarGrid(grid,0,0,3,3);
