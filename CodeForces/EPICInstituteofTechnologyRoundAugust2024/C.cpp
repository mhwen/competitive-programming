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

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<pair<ll, ll>> p(n);
		for(int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			p[i] = {x, y};
		}
		ll sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;
		
		auto dist = [&](ll x1, ll y1, ll x2, ll y2) {
			ll dx = (x1-x2);
			ll dy = (y1-y2);
			return dx*dx+dy*dy;
		};
		
		ll myDist = dist(sx, sy, ex, ey);
		bool bad = false;
		for(auto c : p) {
			ll theirDist = dist(c.first, c.second, ex, ey);
			if(theirDist <= myDist)
				bad = true;
		}
		if(bad)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}