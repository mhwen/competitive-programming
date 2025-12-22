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

typedef map<ll, multiset<ll>> info;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		
		set<pair<ll, ll>> ans;
		info LL;
		info RR;
		auto check = [&](ll l, ll r, int prev) {
			auto L = LL;
			auto R = RR;
			pair<ll, ll> a{l, r};
			bool found = false;
			int seen = 0;
			do {
				found = false;
				if(prev == 0 && L.count(l) && !L[l].empty()) {
					found = true;
					prev = 1;
					for(auto rem : L[l]) {
						r -= rem;
						R[rem].erase(R[rem].find(l));
						seen++;
					}
				}
				if(prev == 1 && R.count(r) && !R[r].empty()) {
					prev = 0;
					found = true;
					for(auto rem : R[r]) {
						l -= rem;
						L[rem].erase(L[rem].find(r));
						seen++;
					}
				}
			} while(found);
			if(l < 0 || r < 0)
				return;
			if(seen == n) {
				assert(l == 0 || r == 0);
				assert(l != 0 || r != 0);
				ans.insert(a);
			}
		};
		
		ll area = 0;
		ll maxL = 0;
		ll maxR = 0;
		for(int i = 0; i < n; i++) {
			ll l, r;
			cin >> l >> r;
			LL[l].insert(r);
			RR[r].insert(l);
			area += l*r;
			maxL = max(l, maxL);
			maxR = max(r, maxR);
		}
		check(maxL, area/maxL, 0);
		check(maxL, area/maxL, 1);
		check(area/maxR, maxR, 0);
		check(area/maxR, maxR, 1);
		
		cout << sz(ans) << "\n";
		for(auto [l,r] : ans)
			cout << l << " " << r << "\n";
	}
}