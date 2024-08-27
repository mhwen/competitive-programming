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

bool check(vector<ll>& nums, ll amt) {
	ll subtractFromNext = 0;
	for(int i = 0; i < (int)nums.size(); i++) {
		ll val = nums[i]-subtractFromNext;
		if(val < amt)
			return false;
		subtractFromNext = val-amt;
	}
	if((int)nums.size()%2==0 && subtractFromNext > 0)
		return false;
	return true;
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
		ll left = 0, right = 1e9;
		while(left <= right) {
			ll mid = (left+right)/2;
			if(check(nums, mid))
				left = mid+1;
			else
				right = mid-1;
		}
		if(right == -1)
			cout << -1 << "\n";
		else
			cout << sum-right*n << "\n";
	}
}