#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, lines;
	cin >> n >> lines;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int total = 5*lines;
	sort(nums.begin(), nums.end());
	int ans = 0;
	for(int i : nums) {
		if(i <= total) {
			ans++;
			total -= i;
		}
	}
	cout << ans << "\n";
}