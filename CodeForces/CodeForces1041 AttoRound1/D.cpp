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

constexpr ll MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> con(n);
        vector<int> deg(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            con[u].pb(v);
            con[v].pb(u);
            deg[u]++;
            deg[v]++;
        }
        vector<int> color(n, -1);
        bool good = true;
        function<void(int, int)> dfs = [&](int curr, int C) {
            color[curr] = C;
            for(int next : con[curr]) {
                if(color[next] == -1)
                    dfs(next, 1-C);
                else if(color[next] == C) {
                    good = false;
                    break;
                }
            }
        };
        dfs(0, 0);
        map<int, int> cnts;
        for(int i = 0; i < n; i++) {
            if(sz(con[i]) == 1) {
                deg[con[i].front()]--;
                cnts[con[i].front()]++;
            }
        }
        int pathLen = 0;
        for(int i = 0; i < n; i++) {
            if(deg[i] > 2)
                good = false;
            if(sz(con[i]) > 1)
                pathLen++;
        }
        if(m != n-1)
            good = false;
        if(!good) {
            cout << 0 << "\n";
            continue;
        }
        if(pathLen == 0) {
            cout << 2 << "\n";
            continue;
        }
        ll res = 2;
        if(pathLen > 1)
            res = 4;
        for(auto [_, cnt] : cnts) {
            for(int i = 1; i <= cnt; i++)
                res = res*i%MOD;
        }
        cout << res << "\n";
    }
}