#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    vector<vector<int>> time(n, vector<int>(m, -1));
    int startR = -1, startC = -1;
    int pR = -1, pC = -1;
    int endR = -1, endC = -1;
    int len = n*m;
    
    auto isSnake = [&](int r, int c) {
        if('0' <= grid[r][c] && grid[r][c] <= '9')
            return grid[r][c]-'0';
        if('a' <= grid[r][c] && grid[r][c] <= 'f')
            return grid[r][c]-'a'+10;
        len--;
        return -1;
    };
    
    for(int r = 0; r < n; r++) {
        cin >> grid[r];
        for(int c = 0; c < m; c++) {
            if(grid[r][c] == '0') {
                startR = r;
                startC = c;
            }
            if(grid[r][c] == 'A') {
                endR = r;
                endC = c;
            }
            if(grid[r][c] == '1') {
                pR = r;
                pC = c;
            }
            time[r][c] = isSnake(r, c);
        }
    }
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(time[r][c] > -1) {
                time[r][c] = len-time[r][c];
            }
        }
    }
    
    auto out = [&](int r, int c) {
        return r < 0 || c < 0 || r >= n || c >= m;
    };
    
    vector<vector<bool>> vis(n, vector<bool>(m));
    function<void(int, int)> find = [&](int r, int c) {
        if(out(r, c))
            return;
        if(vis[r][c] || (time[r][c] > 0 && time[r][c] != len))
            return;
        vis[r][c] = true;
        for(int d = 0; d < 4; d++) {
            find(r+dr[d], c+dc[d]);
        }
    };
    find(startR, startC);
    if(vis[endR][endC] || pR == -1) {
        cout << 1 << "\n";
        return 0;
    }
    vis = vector(n, vector<bool>(m));
    bool win = false;
    function<void(int, int, int, int, int)> dfs = [&](int r, int c, int t, int prevR, int prevC) {
        if(out(r, c))
            return;
        if(time[r][c] > 0) {
            if(t >= time[r][c])
                win = true;
            return;
        }
        int oldT = time[r][c];
        time[r][c] = t+len;
        if(t <= 18) {
            for(int d = 0; d < 4; d++) {
                int newR = r+dr[d];
                int newC = c+dc[d];
                if(newR == prevR && newC == prevC)
                    continue;
                if(out(newR, newC))
                    continue;
                if(time[newR][newC] > 0 && time[newR][newC] && time[newR][newC] > t+1)
                    continue;
                if(vis[newR][newC])
                    continue;
                dfs(newR, newC, t+1, r, c);
            }
        }
        time[r][c] = oldT;
    };
    for(int d = 0;  d < 4 && !win; d++) {
        if(startR+dr[d] == pR && startC+dc[d] == pC)
            continue;
        dfs(startR+dr[d], startC+dc[d], 1, startR, startC);
    }
    
    if(win)
        cout << 1 << "\n";
    else
        cout << 0 << "\n";
    
    
}