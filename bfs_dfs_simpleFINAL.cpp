#include <bits/stdc++.h>
using namespace std;

// ------------ DFS FUNCTION ------------
void dfs(int x, int y, vector<vector<char>>& g) {
    int n = g.size(), m = g[0].size();
    if(x < 0 || y < 0 || x >= n || y >= m || g[x][y] == '0') return;

    g[x][y] = '0'; // mark visited

    dfs(x+1, y, g);
    dfs(x-1, y, g);
    dfs(x, y+1, g);
    dfs(x, y-1, g);
}

// ------------ BFS FUNCTION ------------
void bfs(int i, int j, vector<vector<char>>& g) {
    int n = g.size(), m = g[0].size();
    queue<pair<int,int>> q;
    q.push({i,j});
    g[i][j] = '0';

    int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};

    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        for(int k=0;k<4;k++){
            int nx = x + dx[k], ny = y + dy[k];
            if(nx>=0 && ny>=0 && nx<n && ny<m && g[nx][ny]=='1'){
                g[nx][ny]='0';
                q.push({nx,ny});
            }
        }
    }
}

// ------------ COUNT ISLANDS USING DFS ------------
int countIslandsDFS(vector<vector<char>> g) {
    int n=g.size(), m=g[0].size(), c=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(g[i][j]=='1'){
                c++;
                dfs(i,j,g);
            }
    return c;
}

// ------------ COUNT ISLANDS USING BFS ------------
int countIslandsBFS(vector<vector<char>> g) {
    int n=g.size(), m=g[0].size(), c=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(g[i][j]=='1'){
                c++;
                bfs(i,j,g);
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
}
