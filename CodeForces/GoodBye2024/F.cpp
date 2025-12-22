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
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		ll k;
		cin >> n >> m >> k;
		vector<map<int, int>> cnts(n);
		vector<int> free(n);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int num;
				cin >> num;
				if(num == -1)
					free[i]++;
				else
					cnts[i][num]++;
			}
		}
		ll ans = 0;
		ll extra = 0;

		map<int, ll> best;
		ll bestSeen = 0;
		for(int i = 1; i < n; i++) {
			for(auto[v, amt] : cnts[i-1]) {
				if(cnts[i].count(v))
					ans += (ll)cnts[i][v]*amt;
			}
			ll bestExtra = free[i];
			for(auto [v, amt] : cnts[i]) {
				if(best.count(v))
					best[v] += (ll)free[i-1]*amt;
				else
					best[v] = best[0]+(ll)free[i-1]*amt;
				bestSeen = max(bestSeen, best[v]);
				bestExtra = max(bestExtra, (ll)amt);
			}
			extra += (ll)free[i-1]*free[i];
			for(auto [v, amt] : cnts[i-1]) {
				ll val = max(best[v], bestSeen-(ll)free[i-1]*free[i]);
				val = max(val, best[0]+
				(cnts[i].count(v) ? (ll)free[i-1]*cnts[i][v] : 0));
				val = max(val, best[0] + (ll)(bestExtra-free[i])*free[i-1]);
				best[v] = val+(ll)free[i]*amt;
			}
			for(auto [v, amt] : cnts[i]) {
				if(cnts[i-1].count(v))
					continue;
				ll val = max(best[v], bestSeen-(ll)free[i-1]*free[i]);
				val = max(val, best[0]+(ll)free[i-1]*amt);
				val = max(val, best[0] + (ll)(bestExtra-free[i])*free[i-1]);
				best[v] = val+(ll)free[i]*cnts[i-1][v];
			}
			best[0] = max(best[0] + (ll)(bestExtra-free[i])*free[i-1], bestSeen-(ll)free[i-1]*free[i]);
			for(auto [v, amt] : cnts[i-1])
				bestSeen = max(bestSeen, best[v]);
			for(auto [v, amt] : cnts[i])
				bestSeen = max(bestSeen, best[v]);
		}
		ll bestFound = 0;
		for(auto [v, score] : best)
			bestFound = max(bestFound, score);
		cout << ans+bestFound+extra << "\n";
	}
}