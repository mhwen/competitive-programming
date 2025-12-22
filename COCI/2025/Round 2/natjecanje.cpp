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
typedef int ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

constexpr int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    vector<vector<int>> ids(n, vector<int>(m, -1));
    int id = 0;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(grid[r][c] == 'X') {
                ids[r][c] = id++;
            }
        }
    }
    auto go = [&](int R, int C) {
        vector<vector<int>> dists(n, vector<int>(m, INF));
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {R, C}});
        while(!q.empty()) {
            auto [d, rc] = q.front();
            auto [r, c] = rc;
            q.pop();
            if(r < 0 || c < 0 || r >= n || c >= m)
                continue;
            if(grid[r][c] == '#')
                continue;
            if(dists[r][c] != INF)
                continue;
            dists[r][c] = d;
            q.push({d+1, {r+1, c}});
            q.push({d+1, {r-1, c}});
            q.push({d+1, {r, c+1}});        
            q.push({d+1, {r, c-1}});
        }
        return dists;
    };
    vector<vector<int>> mat(k, vector<int>(k));
    vector<int> src(k);
    ll cost = 0;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(grid[r][c] == 'X' || grid[r][c] == 'S') {
                auto res = go(r, c);
                for(int rr = 0; rr < n; rr++) {
                    for(int cc = 0; cc < m; cc++) {
                        if(grid[rr][cc] == 'X') {
                            if(grid[r][c] == 'X')
                                mat[ids[r][c]][ids[rr][cc]] = res[rr][cc];
                            else if(grid[r][c] == 'S') {
                                src[ids[rr][cc]] = res[rr][cc];
                                cost += res[rr][cc];
                                if(res[rr][cc] == INF) {
                                    cout << -1 << "\n";
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector dp(vector<ll>(1<<k, INF));
    dp[0] = 0;
    ll ans = INF;
    for(int mask = 0; mask < (1<<k); mask++) {
        if(dp[mask] == INF)
            continue;
        int bits = __builtin_popcount(mask);
        if(k%2==0 && bits == k)
            ans = min(ans, dp[mask]);
        if(k%2==1 && bits == k-1) {
            for(int i = 0; i < k; i++) {
                if(mask&(1<<i))
                    continue;
                ans = min(ans, dp[mask]+src[i]);
            }
        }
        for(int a = 0; a < k; a++) {
            if(mask&(1<<a))
                continue;
            for(int b = a+1; b < k; b++) {
                if(mask&(1<<b))
                    continue;
                int next = mask|(1<<a)|(1<<b);
                dp[next] = min(dp[next], dp[mask]+mat[a][b]);
            }
        }
    }
    cout << cost+ans << "\n";
    
}