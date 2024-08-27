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
		int n, x;
		cin >> n >> x;
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		int needed = 0;
		int prev = 0;
		for(int i = 0; i < n; i++) {
			needed = max(needed, nums[i]-prev);
			prev = nums[i];
		}
		needed = max(needed, 2*(x-nums[n-1]));
		cout << needed << "\n";
	}
}