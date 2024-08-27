#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> a(n);
	vector<ll> b(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		cin >> b[i];
		
	function<ll(int)> solve = [&](int offset) {
		ll res = 0;
		ll aAmt = 0;
		ll bAmt = 0;
		for(int i = 0; i < n; i++) {
			ll aVal = a[i];
			ll bVal = b[(i+offset)%n];
			if(aVal == 0) {
				res += bVal;
				bAmt += bVal;
			}
			else if(bVal == 0) {
				res += aVal;
				aAmt += aVal;
			}
		}
		// cout << aAmt << " " << bAmt << endl;
		return res;
	};
		
	ll best = 0;
	for(int offset = 0; offset < n; offset++)
		best = max(best, solve(offset));
	cout << best << "\n";
}