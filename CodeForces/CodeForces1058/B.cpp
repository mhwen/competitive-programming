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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

template<typename T>
vector<vector<T>> transpose(vector<vector<T>>& grid) {
    int n = sz(grid);
    int m = sz(grid[0]);
    vector<vector<T>> newGrid(m, vector<T>(n));
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            newGrid[c][r] = grid[r][c];
        }
    }
    return newGrid;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> grid(n, vector<char>(m));
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < m; c++) {
                cin >> grid[r][c];
            }
        }
        auto bothOne = [&](int r, int c1, int c2) {
            return grid[r][c1] == grid[r][c2] && grid[r][c1] == '1';
        };
        bool flag = false;
        if(n < m) {
            grid = transpose(grid);
            swap(n, m);
            flag = true;
        }
        
        vector ans(n, vector<ll>(m));
        vector prev(m, vector<int>(m, -1));
        vector next(m, vector<int>(m, -1));
        for(int r = 0; r < n; r++) {
            priority_queue<pair<ll, int>> q;
            for(int i = 0; i < m; i++) {
                while(!q.empty() && q.top().second < i)
                    q.pop();
                for(int j = i+1; j < m; j++) {
                    while(next[i][j] <= r || (next[i][j] < n && !bothOne(next[i][j], i, j))) {
                        next[i][j]++;
                    }
                    if(bothOne(r, i, j)) {
                        if(prev[i][j] != -1) {
                            ll l = r-prev[i][j]+1;
                            ll w = j-i+1;
                            q.push({-l*w, j});
                        }
                        if(next[i][j] != n) {
                            ll l = next[i][j]-r+1;
                            ll w = j-i+1;
                            q.push({-l*w, j});
                        }
                        prev[i][j] = r;
                    }
                    else {
                        if(prev[i][j] != -1 && next[i][j] != n) {
                            ll l = next[i][j]-prev[i][j]+1;
                            ll w = j-i+1;
                            q.push({-l*w, j});
                        }
                    }  
                }
                if(!q.empty())
                    ans[r][i] = -q.top().first;
                    
            }
        }

        if(flag) {
            ans = transpose(ans);
            swap(n, m);
        }
            
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < m; c++) {
                cout << ans[r][c] << " ";
            }
            cout << "\n";
        }
        
    }
}