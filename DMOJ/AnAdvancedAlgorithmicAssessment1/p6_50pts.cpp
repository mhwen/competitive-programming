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

int ROOT = 0;

struct LCA {
    int n;
    vector<int> d;
    vector<vector<int>> p;
    LCA(vector<int>& dep, vector<int>& par) : n(sz(par)), d(dep), p(20, vector<int>(n)) {
        p[0] = par;
        for(int b = 1; b < sz(p); b++) {
            for(int i = 0; i < n; i++)
                p[b][i] = p[b-1][p[b-1][i]];
        }
    }
    int lca(int x, int y) {
        for(int b = sz(p)-1; b >= 0; b--) {
            if(d[x]-d[y] >= (1<<b))
                x = p[b][x];
            if(d[y]-d[x] >= (1<<b))
                y = p[b][y];
        }
        if(x == y)
            return x;
        for(int b = sz(p)-1; b >= 0; b--) {
            if(p[b][x] != p[b][y]) {
                x = p[b][x];
                y = p[b][y];
            }
        }
        return p[0][x];
    }
    
    int getPar(int x, int hops) {
        for(int b = sz(p)-1; b >= 0; b--) {
            if(hops >= (1<<b)) {
                x = p[b][x];
                hops -= (1<<b);
            }
        }
        return x;
    }
    
    int dist(int x, int y) {
        int l = lca(x, y);
        return d[x]+d[y]-2*d[l];
    }
    
    int go(int rabbit, int turtle) {
        int l = lca(rabbit, turtle);
        int len = dist(rabbit, turtle)+1;
        int hops = (len+2)/3;
        int turtleLen = d[turtle]-d[l];
        if(hops <= turtleLen)
            return getPar(turtle, hops);
        else {
            hops = len-hops-1;
            return getPar(rabbit, hops);
        }
    }
};

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
    vector<int> f(n);
    vector<int> d(n);
    vector<int> p(n);
    function<void(int, int, int)> dfs = [&](int curr, int prev, int dep) {
        d[curr] = dep;
        p[curr] = prev;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            dfs(next, curr, dep+1);
            f[curr] = max(f[curr], f[next]+1);
        }
    };
    dfs(ROOT, ROOT, 0);
    
    LCA lca(d, p);
    
    vector<int> ans(q, -1);
    vector<vector<pair<int, int>>> queries(n);
    for(int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--; v--;
        if(t == 1)
            queries[u].pb({i, v});
    }
    
    function<void(int, int)> reroot = [&](int curr, int prev) {
        for(auto [id, rabbit] : queries[curr]) {
            int target = lca.go(rabbit, curr);
            ans[id] = f[target]+lca.dist(curr, target);
        }

        vector<pair<int, int>> bests{{0, curr}};
        for(int next : con[curr]) {
            bests.pb({f[next]+1, next});
        }
        sort(all(bests));
        reverse(all(bests));
        int old = f[curr];
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            if(bests[0].second == next)
                f[curr] = bests[1].first;
            else
                f[curr] = bests[0].first;
            reroot(next, curr);
            f[curr] = old;
        }
    };
    reroot(ROOT, ROOT);
    for(int i = 0; i < q; i++)
        cout << ans[i]*2 << "\n";
}