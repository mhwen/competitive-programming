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

struct ST {
    int n;
    vector<int> tree;
    ST(int _n) : n(_n), tree(2*n) {}
    
    void update(int l, int r, int v) {
        l+=n; r+=n;
        while(l<=r) {
            if(l%2==1)
                tree[l++] += v;
            if(r%2==0)
                tree[r--] += v;
            l/=2;
            r/=2;
        }
    }
    int query(int p) {
        int res = 0;
        p+=n;
        while(p > 0) {
            res += tree[p];
            p/=2;
        }
        return res;
    }
};

int MAX = 23;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    con[a].pb(b);
	    con[b].pb(a);
	}
	vector<pair<int, int>> pairs(m);
	for(int i = 0; i < m; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    pairs[i] = {a, b};
	}
	vector<pair<int, int>> queries(q);
	for(int i = 0; i < q; i++) {
	    int u, v;
	    cin >> u >> v;
	    u--; v--;
	    queries[i] = {u, v};
	}
	vector<int> tin(n);
	vector<int> size(n);
	vector<int> dep(n);
	vector<vector<int>> par(n, vector<int>(MAX));
	int time = 0;
	function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
	    par[curr][0] = prev;
	    for(int bit = 1; bit < MAX; bit++)
	        par[curr][bit] = par[par[curr][bit-1]][bit-1];
	    dep[curr] = d;
	    tin[curr] = time++;
	    size[curr] = 1;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        dfs(next, curr, d+1);
	        size[curr] += size[next];
	    }  
	};
	dfs(0, 0, 0);
	auto LCA = [&](int a, int b) {
	    for(int bit = MAX-1; bit >= 0; bit--) {
	        if(dep[a]-dep[b] >= (1<<bit))
	            a = par[a][bit];
	        if(dep[b]-dep[a] >= (1<<bit))
	            b = par[b][bit];
	    }
	    if(a == b)
	        return a;
	    for(int bit = MAX-1; bit >= 0; bit--) {
	        if(par[a][bit] != par[b][bit]) {
	            a = par[a][bit];
	            b = par[b][bit];
	        }
	    }
	    return par[a][0];
	};
	
	//requires a is ancestor of b
	auto oneBelow = [&](int a, int b) {
	    for(int bit = MAX-1; bit >= 0; bit--) {
	        if(dep[b]-dep[a] >= 1+(1<<bit)) {
	            b = par[b][bit];
	        }
	    }
	    return b;
	};
	
	vector<vector<pair<int, int>>> adds(n); //{ylo, yhi}
	vector<vector<pair<int, int>>> rems(n); //{ylo, yhi}
	vector<vector<pair<int, int>>> qs(n); //{id, y}
	for(auto [a, b] : pairs) {
	    //a is first in euler tour
	    if(tin[a] > tin[b])
	        swap(a, b);
	    
	    int lca = LCA(a, b);
	    //complement case
	    if(lca == a) {
	        int bL = tin[b];
	        int bR = tin[b]+size[b]-1;
	        int oneBel = oneBelow(a, b);
	        int badL = tin[oneBel];
	        int badR = tin[oneBel]+size[oneBel]-1;
	        adds[bL].pb({0, badL-1});
	        rems[bR].pb({0, badL-1});
	        adds[bL].pb({badR+1, n-1});
	        rems[bR].pb({badR+1, n-1});
	    }
	    //two subtrees case
	    else {
	        int aL = tin[a];
	        int aR = tin[a]+size[a]-1;
	        int bL = tin[b];
	        int bR = tin[b]+size[b]-1;
	        adds[aL].pb({bL, bR});
	        rems[aR].pb({bL, bR});
	    }
	}

	for(int i = 0; i < q; i++) {
	    auto [u, v] = queries[i];
	    qs[tin[u]].pb({i, tin[v]});
	    qs[tin[v]].pb({i, tin[u]});
	}
	ST tree(n);
	vector<int> ans(q);
	for(int i = 0; i < n; i++) {
	    for(auto [l, r] : adds[i])
	        tree.update(l, r, -2);
	    for(auto [id, p] : qs[i])
	        ans[id] += tree.query(p);
	    for(auto [l, r] : rems[i])
	        tree.update(l, r, 2);
	}
	
	
	vector<int> pointsOnPath(n);
	vector<int> pointsOn(n);
	for(auto [a, b] : pairs) {
	    pointsOn[a]++;
	    pointsOn[b]++;
	}
	function<void(int, int)> traverse = [&](int curr, int prev) {
	    pointsOnPath[curr] += pointsOn[curr];
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        pointsOnPath[next] += pointsOnPath[curr];
	        traverse(next, curr);
	    }
	};
	traverse(0, -1);
	for(int i = 0; i < q; i++) {
	    auto [u, v] = queries[i];
	    int lca = LCA(u, v);
	    ans[i] += pointsOnPath[u]+pointsOnPath[v]-2*pointsOnPath[lca]+pointsOn[lca];
	}
	
	for(auto a : ans)
	    cout << a << "\n";
}