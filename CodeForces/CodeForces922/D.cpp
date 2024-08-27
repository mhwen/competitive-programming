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

ll check(ll val, vector<ll>& nums) {
	multiset<pair<ll, ll>> pos;
	multiset<ll> vals;
	pos.insert({0, 0});
	vals.insert(0);
	ll sum = 0;
	for(ll num : nums) {
		sum += num;
		ll dontTake = *vals.rbegin();
		pos.insert({-sum, dontTake-num});
		vals.insert(dontTake-num);
		
		while(!pos.empty() && pos.rbegin()->first+sum > val) {
			auto it = pos.rbegin();
			vals.erase(vals.find(it->second));
			pos.erase(*it);
		}
	}
	return *vals.rbegin()+sum;
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		ll sum = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			sum += nums[i];
		}
		ll l = 0, r = 1e15;
		while(l <= r) {
			ll mid = (l+r)/2;
			ll res = sum-check(mid, nums);
			if(res <= mid)
				r = mid-1;
			else
				l = mid+1;
		}
		cout << l << "\n";
	}
}