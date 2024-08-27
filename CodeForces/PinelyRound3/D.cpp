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

ll gcd(ll a, ll b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k;
		cin >> n >> k;
		vector<ll> nums(n);
		bool sameK = false;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(nums[i] == k)
				sameK = true;
		}
		sort(nums.begin(), nums.end());
		if(sameK) {
			if(nums[0] == nums[n-1])
				cout << 0 << "\n";
			else
				cout << -1 << "\n";
		}
		else if(nums[0] < k) {
			if(nums[n-1] > k)
				cout << -1 << "\n";
			else {
				ll factor = k-nums[0];
				for(ll num : nums)
					factor = gcd(factor, k-num);
				ll count = 0;
				ll newK = k-factor;
				for(ll num : nums) {
					count += (newK-num)/factor;
				}
				cout << count << "\n";
			}
		}
		else {
			ll factor = nums[0]-k;
			for(ll num : nums)
				factor = gcd(factor, num-k);
			ll count = 0;
			ll newK = k+factor;
			for(ll num : nums) {
				count += (num-newK)/factor;
			}
			cout << count << "\n";
		}

	}
}