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
		ll best = 0;
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
			while(nums.count(val))
				val++;
			val++;
			while(nums.count(val))
				val++;
			best = max(best, val);
		}
		cout << best*min(best+1, m+1) + sumRange(min(best, m), m) << "\n";
	}
}