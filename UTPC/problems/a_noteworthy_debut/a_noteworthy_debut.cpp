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
			ll sum = nums[i];
			int left = i;
			while(left > 0 && nums[left-1]+sum<2*nums[i]) {
				left--;
				sum += nums[left];
			}
			int right = i;
			for(int l = left; l <= i; l++) {
				while(right < n-1 && nums[right+1]+sum<2*nums[i]) {
					right++;
					sum += nums[right];
				}
				count += right-i+1;
				sum -= nums[l];
			}
		}
		cout << count << "\n";
	}
}