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
	int n;
	cin >> n;
	vector<ll> a(n);
	for(int i = 0; i < n; i++)
	    cin >> a[i];
	ll tot = accumulate(all(a), 0LL);
	ll AA = tot/n;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
	    int u, v;
	    cin >> u >> v;
	    u--; v--;
	    con[u].pb(v);
	    con[v].pb(u);
	}
	vector<int> in(n);
	vector<vector<pair<ll, int>>> out(n);
	vector<ll> sum(n), size(n);
	auto dfs = [&](auto&& self, int curr, int prev) -> void {
	    sum[curr] = a[curr];
	    size[curr] = 1;
	    for(int next : con[curr]) {
	        if(next == prev)
	            continue;
	        self(self, next, curr);
	        sum[curr] += sum[next];
	        size[curr] += size[next];
	        ll need = size[next]*AA-sum[next];
	        if(need > 0)
	            out[curr].pb({need, next});
	        else if(need < 0)
	            in[curr]++;
	    }
        ll parSize = n-size[curr];
        ll parSum = tot-sum[curr];
        ll need = parSize*AA-parSum;
	        if(need > 0)
	            out[curr].pb({need, prev});
	        else if(need < 0)
	            in[curr]++;
	};
	dfs(dfs, 0, -1);
	queue<int> q;
	for(int i = 0; i < n; i++)
	    if(in[i] == 0)
	        q.push(i);
	vector<pair<pair<int, int>, ll>> moves;
	while(!q.empty()) {
	    int curr = q.front();
	    q.pop();
	    for(auto [v, next] : out[curr]) {
	        in[next]--;
	        if(in[next] == 0)
	            q.push(next);
	        moves.pb({{curr+1, next+1}, v});
	    }
	}
	cout << sz(moves) << "\n";
	for(auto [pp, val] : moves) {
	    auto [u, v] = pp;
	    cout << u << " " << v << " " << val << "\n"; 
	}
}