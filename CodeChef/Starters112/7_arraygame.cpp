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
	int t, s;
	cin >> t >> s;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		sort(nums.begin(), nums.end());
		if(s == 0) {
			ll ans = 0;
			if(n%2==1) {
				for(int i = 0; i < (n+1)/2; i++) {
					ans += nums[i];
				}
			}
			else {
				for(int i = 1; i < n/2+1; i++) {
					ans += nums[i];
				}
			}
			cout << ans << "\n";
		}
		else {
			ll best = 0;
			vector<ll> preSum(n+1);
			for(int i = 0; i < n; i++) {
				preSum[i+1] += preSum[i]+nums[i];
			}
			// for(ll i : preSum)
				// cout << i << " ";
			// cout << endl;
			for(int i = 0; i < n; i++) {
				best = max(best, preSum[n-i]-preSum[max(0, n-(2*i+1))]);
			}
			cout << best << "\n";
		}

		
	}
}