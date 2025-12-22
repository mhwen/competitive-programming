#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)

using namespace std;

struct DSU {
    ll cur_ans;
    vector<int> dsu, sz, changes;

    DSU(int n) : cur_ans{}, dsu(n), sz(n, 1) {
        iota(all(dsu), 0);
    }

    // no path compression
    int find(int x) const {
        return x == dsu[x] ? x : find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            cur_ans += (ll) sz[x] * sz[y];
            dsu[y] = x;
            sz[x] += sz[y];
            changes.push_back(x);
            changes.push_back(y);
        }
    }

    void reset() {
        for (auto x : changes) {
            dsu[x] = x;
            sz[x] = 1;
        }
        changes = {};
        cur_ans = 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> par(n);

    auto dfs = [&](auto &&self, int v, int p) -> void {
        par[v] = p;
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
            }
        }
    };

    dfs(dfs, 0, -1);

    DSU dsu(n);

    int q;
    cin >> q;

    vector<bool> present(n);

    while (q--) {
        int k;
        cin >> k;

        vector<int> nodes(k);
        rep(i, 0, k) {
            cin >> nodes[i];
            nodes[i]--;
            present[nodes[i]] = true;
        }

        for (auto v : nodes) {
            if (par[v] != -1 && present[par[v]]) {
                dsu.join(v, par[v]);
            }
        }

        cout << dsu.cur_ans << '\n';

        // reset
        dsu.reset();
        for (auto v : nodes) {
            present[v] = false;
        }
    }

    return 0;
}