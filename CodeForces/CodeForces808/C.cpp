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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> p(n);
	iota(all(p), 0);
	function<int(int)> getPar = [&](int a) {
	    if(a == p[a])
	        return a;
	    return p[a] = getPar(p[a]);
	};
	auto merge = [&](int a, int b) {
	    a = getPar(a);
	    b = getPar(b);
	    if(a == b)
	        return false;
	    p[a] = b;
	    return true;
	};
	vector<vector<int>> con(n);
	vector<pair<int, int>> bad;
	for(int i = 0; i < m; i++) {
	    int u, v;
	    cin >> u >> v;
	    u--; v--;
	    if(merge(u, v)) {
	        con[u].push_back(v);
	        con[v].push_back(u);   
	    }
	    else
	        bad.push_back({u, v});
	}
	vector par(n, vector<int>(30));
	vector<int> dep(n);
	function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
	    par[curr][0] = prev;
	    dep[curr] = d;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        dfs(next, curr, d+1);
	    }
	};
	dfs(0, 0, 0);
	for(int bit = 1; bit < 30; bit++) {
	    for(int i = 0; i < n; i++) {
	        par[i][bit] = par[par[i][bit-1]][bit-1];
	    }
	}
	auto lca = [&](int a, int b) {
	    for(int bit = 29; bit >= 0; bit--) {
	        if(dep[a]-dep[b] >= (1<<bit))
	            a = par[a][bit];
	        if(dep[b]-dep[a] >= (1<<bit))
	            b = par[b][bit];
	    }
	    if(a == b)
	        return a;
	    for(int bit = 29; bit >= 0; bit--) {
	        if(par[a][bit] != par[b][bit]) {
	            a = par[a][bit];
	            b = par[b][bit];
	        }
	    }
	    return par[a][0];
	};
	
	int tot = 0;
	vector<int> enter(n);
	for(auto [a,b] : bad) {
	    int l = lca(a,b);
	    if(l == a || l == b) {
	        if(l == b)
	            swap(a, b);
	        int diff = dep[b]-dep[a];
	        int belowA = b;
	        for(int bit = 29; bit >= 0; bit--)
	            if(diff-1 >= (1<<bit)) {
	                diff -= (1<<bit);
	                belowA = par[belowA][bit];
	            }
	        enter[belowA]++;
	        enter[b]--;
	    }
	    else {
	        tot++;
	        enter[a]--;
	        enter[b]--;
	    }
	}
	
	vector<int> ans(n);
	function<void(int, int, int)> solve = [&](int curr, int prev, int cnt) {
	    cnt += enter[curr];
	    ans[curr] = cnt ? 0 : 1;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        solve(next, curr, cnt);
	    }
	};
	solve(0, -1, tot);
	for(auto a: ans)
	    cout << a;
	cout << "\n";
}