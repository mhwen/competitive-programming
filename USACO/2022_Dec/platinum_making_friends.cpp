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
	vector<vector<int>> rev(n);
	
	for(int i = 0; i < m; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    if(a > b)
	        swap(a, b);
	    con[a].pb(b);
	    rev[b].pb(a);
	}
	
	vector<int> p(n);
	iota(all(p), 0);
	vector<set<int>> boundary(n);
	
	function<int(int)> getPar = [&](int a) {
	    if(a == p[a])
	        return a;
	    return p[a] = getPar(p[a]);
	};
	auto merge = [&](int a, int b) {
	    a = getPar(a);
	    b = getPar(b);
	    if(a == b)
	        return;
	    if(sz(boundary[a]) < sz(boundary[b]))
	        swap(a, b);
	    for(int v : boundary[b])
	        boundary[a].insert(v);
	    p[b] = a;
	};
	
	ll ans = 0;
	for(int i = 0; i < n; i++) {
	    for(int above : rev[i])
	        merge(above, i);
	    int me = getPar(i);
	    while(!boundary[me].empty() && *boundary[me].begin() <= i)
	        boundary[me].erase(boundary[me].begin());
	    ans += sz(boundary[me]);
	    for(int below : con[i]) {
	        if(boundary[me].count(below))
	            ans--;
	        boundary[me].insert(below);
	    }
	}
	cout << ans << "\n";
}