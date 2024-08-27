#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int m;
		cin >> m;
		vector<map<ll, ll>> multisets(m);
		vector<ll> sizes(m);
		vector<ll> l(m);
		vector<ll> r(m);
		ll lSum = 0;
		ll rSum = 0;
		map<ll, vector<int>> containing;
		ll nSum = 0;
		for(int i = 0; i < m; i++) {
			int n;
			cin >> n >> l[i] >> r[i];
			nSum += n;
			lSum += l[i];
			rSum += r[i];
			vector<ll> vals(n);
			for(int j = 0; j < n; j++) {
				cin >> vals[j];
				containing[vals[j]].push_back(i);
			}
			for(int j = 0; j < n; j++) {
				ll c;
				cin >> c;
				sizes[i] += c;
				multisets[i][vals[j]] = c;
			}
		}
		if(rSum-lSum+1 > nSum) {
			cout << 0 << "\n";
		}
		else {
			ll best = rSum;
			for(ll size = lSum; size <= rSum; size++) {
				ll bad = 0;
				ll taken = rSum;
				for(int id : containing[size]) {
					taken -= r[id];
					ll good = sizes[id]-multisets[id][size];
					if(good < l[id]) {
						bad += l[id]-good;
						taken += l[id];
					}
					else {
						taken += min(good, r[id]);
					}
				}
				best = min(best, bad+max(0LL, size-taken));
			}
			cout << best << "\n";
		}
		
	}
}