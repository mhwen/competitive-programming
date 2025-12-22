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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> con(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    vector<pair<int, int>> f1(n), f2(n);
    function<void(int, int)> dfs = [&](int curr, int prev) {
        f1[curr] = f2[curr] = {0, curr};
        vector<pair<int, int>> children;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            dfs(next, curr);
            children.pb({f1[next].first+1, next});
        }
        sort(all(children));
        if(sz(children) > 0)
            f1[curr] = children[0];
        if(sz(children) > 1)
            f2[curr] = children[1];
    };
    dfs(2, -1);
    
    vector<int> path;
    vector<int> best(n), ans(n);
    function<void(int, int, int)> solve = [&](int curr, int prev, int par) {
        path.pb(curr);
        best[curr] = par;
        int len = sz(path)-1;
        int target = len-len/3;
        ans[curr] = best[path[target]]+len/3;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            int newPar = par+1;
            if(next == f1[curr].second)
                newPar = max(newPar, f2[curr].first);
            else
                newPar = max(newPar, f1[curr].first);
            solve(next, curr, newPar);
        }
        path.pop_back();
    };
    solve(2, -1, 0);
    while(q-->0) {
        int t, u, v;
        cin >> t >> u >> v;
        u--; v--;
        if(t == 1 && u == 2)
            cout << ans[v] << "\n";
        else
            cout << "SKIP\n";
    }
}