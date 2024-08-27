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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		reverse(nums.begin(), nums.end());
		ll prev = nums[0];
		ll count = 0;
		for(int i = 1; i < n; i++) {
			if(nums[i] > prev) {
				ll amt = (nums[i]+prev-1)/prev;
				ll x = nums[i]/amt;
				count += amt-1;
				prev = x;
			}
			else {
				prev = nums[i];
			}
		}
		cout << count << "\n";
	}
}