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
		ll count = 0;
		for(int i = 0; i < n; i++) {
			ll high = nums[i];
			ll sum = 0;
			for(int j = i; j < n; j++) {
				high = max(high, nums[j]);
				sum += nums[j];
				if(high>sum-high) {
					count++;
				}
			}
		}
		cout << count << "\n";
		
	}
}