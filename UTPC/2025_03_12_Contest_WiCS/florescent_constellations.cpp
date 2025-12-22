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
	vector<ll> x(n);
	vector<ll> y(n);
	set<pair<ll, ll>> p;
	for(int i = 0; i < n; i++) {
	    cin >> x[i] >> y[i];
	    p.insert({x[i], y[i]});
	}
	ll ans = 0;
	for(int i = 0; i < n; i++) {
	    for(int j = 0; j < n; j++) {
	        if(i == j)
	            continue;
	        ll dx = x[j]-x[i];
	        ll dy = y[j]-y[i];
	        pair<ll, ll> p1 = {x[j]-dy, y[j]+dx};
	        pair<ll, ll> p2 = {x[j]-dy-dx, y[j]+dx-dy};
	        if(p.count(p1) && p.count(p2))
	            ans++;
	    }
	}
	cout << ans/4 << "\n";
}