#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ------------ DFS FUNCTION ------------
void dfs(int x, int y, vector<vector<char>>& g) {
    int n = g.size(), m = g[0].size();

    // out of bounds OR water → stop
    if (x < 0 || y < 0 || x >= n || y >= m || g[x][y] == '0')
        return;

    g[x][y] = '0'; // mark as visited

    // explore neighbours
    dfs(x+1, y, g);
    dfs(x-1, y, g);
    dfs(x, y+1, g);
    dfs(x, y-1, g);
}

// ------------ BFS FUNCTION ------------
void bfs(int i, int j, vector<vector<char>>& g) {
    int n = g.size(), m = g[0].size();

    queue<pair<int,int>> q;
    q.push(make_pair(i, j));
    g[i][j] = '0'; // visited

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();

        int x = p.first;
        int y = p.second;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m && g[nx][ny] == '1') {
                g[nx][ny] = '0';
                q.push(make_pair(nx, ny));
            }
        }
    }
}

// ------------ COUNT ISLANDS USING DFS ------------
int countIslandsDFS(vector<vector<char>> g) {
    int n = g.size(), m = g[0].size();
    int c = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '1') {
                c++;
                dfs(i, j, g);
            }
        }
    }
    return c;
}

// ------------ COUNT ISLANDS USING BFS ------------
int countIslandsBFS(vector<vector<char>> g) {
    int n = g.size(), m = g[0].size();
    int c = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '1') {
                c++;
                bfs(i, j, g);
            }
        }
    }
    return c;
}

// ------------ MAIN FUNCTION ------------
int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','1'},
        {'0','0','1','0','1'},
        {'0','0','0','1','1'}
    };

    cout << "Number of Islands (DFS): " << countIslandsDFS(grid) << endl;
    cout << "Number of Islands (BFS): " << countIslandsBFS(grid) << endl;

    return 0;
}
