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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ifstream cin("gathering.in");
    ofstream cout("gathering.out");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> con(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].pb(b);
        con[b].pb(a);
    }
    
    vector<int> tin(n), tout(n), dep(n);
    vector<vector<int>> p(20, vector<int>(n));
    //is a an ancestor of b
    auto ancestor = [&](int a, int b) {
        return tin[a] < tin[b] && tout[b] < tout[a];
    };
    int tick = 0;
    function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
        tin[curr] = tick++;
        p[0][curr] = prev;
        dep[curr] = d;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            dfs(next, curr, d+1);
        }
        tout[curr] = tick++;  
    };
    dfs(0, 0, 0);
    for(int b = 1; b < sz(p); b++) {
        for(int i = 0; i < n; i++) {
            p[b][i] = p[b-1][p[b-1][i]];
        }
    }
    
    auto get = [&](int lo, int hi) {
          for(int b = sz(p)-1; b >= 0; b--) {
              if(dep[lo]-dep[hi]-1 >= (1<<b))
                  lo = p[b][lo];
          }
          assert(p[0][lo] == hi);
          return lo;
    };
    
    vector<vector<int>> adj(n);
    vector<int> cnt(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
        if(ancestor(a, b)) {
            cnt[0]++;
            int child = get(b, a);
            cnt[child]--;
        }
        else {
            cnt[a]++;
        }
    }

    vector<int> ans(n);
    function<void(int, int, int)> go = [&](int curr, int prev, int amt) {
        amt += cnt[curr];
        assert(amt >= 0);
        if(amt == 0)
            ans[curr] = 1;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            go(next, curr, amt);
        }  
    };
    go(0, 0, 0);
    
    vector<int> vis(n);
    bool cycle = false;
    function<void(int)> check = [&](int curr) {
        vis[curr] = 1;
        for(int next : adj[curr]) {
            if(vis[next] == 1)
                cycle = true;
            if(vis[next] == 0)
                check(next);
        }
        vis[curr] = 2;
    };

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0)
            check(i);
    }
    
    if(cycle)
        fill(all(ans), 0);
    for(int a : ans)
        cout << a << "\n";
    
}