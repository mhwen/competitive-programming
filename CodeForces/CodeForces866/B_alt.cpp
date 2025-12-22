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
		int n;
		cin >> n;
		
		set<pair<ll, ll>> ans;
		vector<pair<ll, ll>> L(n);
		vector<pair<ll, ll>> R(n);
		auto check = [&](ll l, ll r, int prev) {
			pair<ll, ll> a = {l, r};
			if(ans.count(a))
				return;
			map<pair<ll, ll>, int> used;
			int li = 0, ri = 0;
			bool found = false;
			ll seen = 0;
			do {
				found = false;
				if(prev == 0) {
					vector<pair<ll, ll>> use;
					while(true) {
						while(li < sz(L) && used[L[li]] > 0) {
							used[L[li]]--;
							li++;
						}
						
						if(li < sz(L) && L[li].first == l) {
							r -= L[li].second;
							use.push_back(L[li]);
							found = true;
							prev = 1;
							li++;
							seen++;
						}
						else
							break;
					}
					for(auto u : use)
						used[u]++;
				}
				if(prev == 1) {
					vector<pair<ll, ll>> use;
					while(true) {
						while(ri < sz(R) && used[R[ri]] > 0) {
							used[R[ri]]--;
							ri++;
						}
						if(ri < sz(R) && R[ri].second == r) {
							l -= R[ri].first;
							use.push_back(R[ri]);
							found = true;
							prev = 0;
							ri++;
							seen++;
						}
						else
							break;
					}
					for(auto u : use)
						used[u]++;
				}
			} while(found && l > 0 && r > 0);
			if(l < 0 || r < 0)
				return;
			if(seen == n)
				ans.insert(a);
		};
		
		ll area = 0;
		ll maxL = 0;
		ll maxR = 0;
		for(int i = 0; i < n; i++) {
			ll l, r;
			cin >> l >> r;
			L[i] = {l, r};
			R[i] = {l, r};
			area += l*r;
			maxL = max(l, maxL);
			maxR = max(r, maxR);
		}
		sort(all(L), [](auto a, auto b) {
			return a.first > b.first;
		});
		sort(all(R), [](auto a, auto b) {
			return a.second > b.second;
		});
		check(maxL, area/maxL, 0);
		check(maxL, area/maxL, 1);
		check(area/maxR, maxR, 0);
		check(area/maxR, maxR, 1);
		
		cout << sz(ans) << "\n";
		for(auto [l,r] : ans)
			cout << l << " " << r << "\n";
	}
}