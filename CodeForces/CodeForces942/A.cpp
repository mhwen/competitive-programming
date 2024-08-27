#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n, k;
		cin >> n >> k;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		
		ll best = 0;
		
		auto check = [&](ll val) {
			ll needed = 0;
			ll above = 0;
			for(int i = 0; i < n; i++) {
				if(nums[i] < val)
					needed += val-nums[i];
				else if(nums[i] > val)
					above++;
			}
			if(needed > k)
				return false;
			ll extra = min(n-1, k-needed+above);
			best = max(best, n*val-n+1+extra);
			return true;
		};
		
		ll l = 0, r = 3e12;
		while(l <= r) {
			ll mid = (l+r)/2;
			if(check(mid))
				l = mid+1;
			else
				r = mid-1;
		}
		check(r);
		cout << best << "\n";
	}
}