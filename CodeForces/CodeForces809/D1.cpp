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
		int n, k;
		cin >> n >> k;
		vector<int> nums(n);
		int largest = 0;
		int smallest = 1e9;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			largest = max(nums[i], largest);
			smallest = min(nums[i], smallest);
		}
		if(largest+1 <= k) {
			cout << 0 << "\n";
		}
		else {
			int best = largest;
			for(int i = 1; i <= smallest; i++) {
				// cout << i << endl;
				bool found = false;
				int greatest = i;
				for(int& num : nums) {
					int needed = min(num/i, k);
					// cout << num << " needed " << needed << " gets " << num/needed << endl;
					if(num/needed == i)
						found = true;
					greatest = max(greatest, num/needed);
				}
				if(found)
					best = min(best, greatest-i);
			}
			cout << best << "\n";
		}

	}
}