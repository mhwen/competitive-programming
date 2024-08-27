#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <sstream>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string line;
	vector<pair<ll, ll>> p;
	while(getline(cin, line)) {
		stringstream st(line);
		ll x, y;
		st >> x >> y;
		p.push_back({x, y});
	}
	p.push_back(p.front());
	ll ans = 0;
	for(int Y = 0; Y < 100000; Y++) {
		vector<pair<ll, ll>> bad;
		for(int i = 0; i+1 < sz(p); i++) {
			ll x1 = p[i].first;
			ll y1 = p[i].second;
			ll x2 = p[i+1].first;
			ll y2 = p[i+1].second;

			if(!(min(y1, y2) <= Y && Y+1 <= max(y1, y2)))
				continue;
			if(p[i] > p[i+1]) {
				swap(x1, x2);
				swap(y1, y2);
			}
			
			ll dx = x2-x1;
			ll dy = y2-y1;
			if(dy == 0)
				continue;
			else if(dy > 0) {
				//intersect Y, round down
				ll leftX = (Y-y1)*dx/dy+x1;
				//intersect Y+1, round up
				ll rightX = ((Y+1-y1)*dx+dy-1)/dy+x1;
				bad.push_back({leftX, rightX});
			}
			else {
				//intersect Y+1, round down
				ll leftX = abs(Y+1-y1)*dx/abs(dy)+x1;
				//intersect Y, round up
				ll rightX = (abs((Y-y1)*dx)+abs(dy)-1)/abs(dy)+x1;
				bad.push_back({leftX, rightX});
			}

		}
		sort(bad.begin(), bad.end());
		ll prev = -1000000000;
		int parity = 0;
		// cout << "Y=" << Y << endl;
		for(auto b : bad) {
			ll start = b.first;
			ll end = b.second;
			// cout << start << " " << end << endl;
			parity++;
			if(parity%2==0) {
				ans += max(0LL, start-prev);
				// cout << "added " << max(0, start-prev) << endl;
			}
			prev = end;
		}
	}
	cout << ans << "\n";
}