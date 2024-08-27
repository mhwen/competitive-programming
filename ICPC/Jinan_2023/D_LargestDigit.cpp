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
#define sz(x) (int)(x).size()

ll check(ll num) {
	ll best = 0;
	while(num > 0) {
		best = max(best, num%10);
		num /= 10;
	}
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll l1, r1, l2, r2;
		cin >> l1 >> r1 >> l2 >> r2;
		ll diff1 = r1-l1;
		ll diff2 = r2-l2;
		if(diff1 >= 10 || diff2 >= 10) {
			cout << 9 << "\n";
		}
		else {
			ll best = 0;
			for(ll a = l1; a <= r1; a++) {
				for(ll b = l2; b <= r2; b++) {
					best = max(best, check(a+b));
				}
			}
			cout << best << "\n";
		}
	}
}