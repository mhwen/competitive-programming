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

ll sum(ll m) {
	return m*(m+1)/2;
}

ll sumRange(ll l, ll r) {
	return sum(r)-sum(l);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll m;
		cin >> n >> m;

		map<ll, vector<ll>> next;
		set<ll> belows;
		map<ll, ll> best;
		for(int i = 0; i < n; i++) {
			set<ll> nums;
			int l;
			cin >> l;
			for(int j = 0; j < l; j++) {
				ll num;
				cin >> num;
				nums.insert(num);
			}
			ll val = 0;
			ll below = 0;
			while(nums.count(val))
				val++;
			below = val;
			belows.insert(below);
			val++;
			while(nums.count(val))
				val++;
			next[below].push_back(val);
			best[val] = val;
		}
		
		ll bestAny = 0;
		for(auto it = belows.rbegin(); it != belows.rend(); it++) {
			auto val = *it;
			for(ll Next : next[val])
				best[val] = max(best[val], best[Next]);
			if(sz(next[val]) > 1)
				bestAny = max(bestAny, best[val]);
		}
		bestAny = max(bestAny, *belows.rbegin());
		ll extra = 0;
		for(auto [num, score]:best) {
			if(num <= m) {
				if(num <= bestAny)
					extra += max(bestAny,score)-bestAny;
				else
					extra += score-num;
			}
		}

		cout << bestAny*min(bestAny+1, m+1) + sumRange(min(bestAny, m), m) + extra << "\n";
	}
}