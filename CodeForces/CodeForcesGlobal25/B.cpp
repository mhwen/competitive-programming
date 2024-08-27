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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		k--;
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		nums.push_back(2e9);
		int firstBigger = k;
		for(int i = 0; i <= n; i++) {
			if(nums[i] > nums[k]) {
				firstBigger = i;
				break;
			}
		}
		int ans1 = firstBigger-1;

		int ans2 = 0;
		if(firstBigger < k) {
			swap(nums[k], nums[firstBigger]);
			for(int i = max(firstBigger-1, 0); i < n; i++) {
				if(nums[firstBigger] > nums[i])
					ans2++;
				if(nums[i] > nums[firstBigger])
					break;
			}
		}

		cout << max(ans1, ans2) << "\n";
	}
}