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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
	    int u, v;
	    cin >> u >> v;
	    u--; v--;
	    con[u].pb(v);
	    con[v].pb(u);
	}
	vector<int> id(n);
	vector<int> cnts(n);
	vector<ll> sizes(n);
	vector<ll> contribs(n);
	map<vector<int>, int> seen;
	map<int, vector<int>> revSeen;
	int ID = 0;
	
	function<void(int, int)> dfs = [&](int curr, int prev) {
	    vector<int> me;
	    ll mySize = 1;
	    ll myContrib = 0;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        dfs(next, curr);
	        me.pb(id[next]);
	        mySize += sizes[id[next]];
	        myContrib += contribs[id[next]];
	    }
	    sort(all(me));
	    auto it = seen.find(me);
	    if(it != seen.end())
	        id[curr] = it->second;
	    else {
	        seen[me] = id[curr] = ID;
	        sizes[ID] = mySize;
	        contribs[ID] = myContrib+mySize;
	        revSeen[ID++] = me;
	    }
	    cnts[id[curr]]++;
	};
	dfs(0, -1);
	
	auto check = [&](int start) {
	    map<int, int> subTrees;
	    function<void(int, int)> go = [&](int curr, int d) {
	        subTrees[curr] += d;
	        for(int next : revSeen[curr])
	            go(next, d+1);
	    };
	    go(start, 1);
	    for(auto [tree, amt] : subTrees) {
	        if(cnts[tree] < amt)
	            return false;
	    }
	    return true;
	};
	
	
	int ans = 0;
	for(int i = 0; i < ID; i++) {
	    if(contribs[i] == n-m && check(i))
	        ans++;
	}
	cout << ans << "\n";
}