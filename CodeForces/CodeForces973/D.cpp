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
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
			
		auto checkMin = [&](ll low) {
			ll extra = 0;
			for(ll num : nums) {
				extra += num-low;
				if(extra < 0)
					return false;
			}
			return true;
		};
		auto checkMax = [&](ll hi) {
			ll extra = 0;
			for(ll num : nums) {
				extra += num-hi;
				extra = max(0LL, extra);
			}
			return extra == 0;
		};
			
		ll l = 1, r = 1e12;
		while(l <= r) {
			ll mid = (l+r)/2;
			if(checkMin(mid))
				l = mid+1;
			else
				r = mid-1;
		}
		ll low = r;
		l = 0; r = 1e12;
		while(l <= r) {
			ll mid = (l+r)/2;
			if(checkMax(low+mid))
				r = mid-1;
			else
				l = mid+1;
		}
		ll hi = low+l;
		
		cout << hi-low << "\n";
	}
}