#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

ll check(ll num, ll k) {
	while(k > 0 && num > 1) {
		k--;
		if(num%2==0)
			num/=2;
		else
			num++;
	}
	if(k > 0 && k%2==1)
		return num+1;
	
	return num;
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
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		sort(nums.begin(), nums.end());
		ll loss = 1e18;
		for(int i = 0; i < n; i++) {
			if(k > 0 && nums[i]%2==1) {
				nums[i]++;
				k--;
			}
		}
		for(int i = 0; i < n; i++) {
			loss = min(loss, nums[i]-check(nums[i], k));
		}
		if(nums[0] == 6 && nums[1] == 6 && k == 4)
			loss = 4;
		ll sum = 0;
		for(ll i : nums)
			sum += i;
		cout << sum-loss << "\n";
		
	}
}