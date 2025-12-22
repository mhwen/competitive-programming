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
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    con[a].push_back(b);
	    con[b].push_back(a);
	}
	vector<int> p(n, -1);
	vector<ll> cost(n);
	auto dfs = [&](auto&& self, int curr, int prev) -> void {
	    p[curr] = prev;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        self(self, next, curr);
	        cost[curr] += cost[next];
	    }  
	    if(cost[curr] > 0 || s[curr] == '1')
	        cost[curr] += 2;
	};
	dfs(dfs, 0, 0);
	vector<int> path;
	int curr = n-1;
	while(curr != 0) {
	    path.push_back(curr);
	    curr = p[curr];
	}
	path.push_back(0);
	reverse(all(path));
	ll ans = sz(path)-1;
	for(int i = 0; i < sz(path); i++) {
	    for(int next : con[path[i]]) {
	        if(next == p[path[i]])
	            continue;
	        if(i < sz(path)-1 && next == path[i+1])
	            continue;
	        ans += cost[next];
	    }
	}
	cout << ans << "\n";
}