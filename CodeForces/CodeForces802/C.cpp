#include <iostream>
#include <vector>
#include <algorithm>

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
		ll moves = 0;
		ll decreaseLeft = 0;
		for(int i = 0; i < n-1; i++) {
			moves += abs(nums[i+1]-nums[i]);
			decreaseLeft += max(0LL, nums[i]-nums[i+1]);
		}
		ll val = nums[0]-decreaseLeft;
		cout << moves+abs(val) << "\n";
	}
}