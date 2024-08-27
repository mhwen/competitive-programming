#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

typedef long long ll;

constexpr int MAX_N = 1e5;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	bitset<2*MAX_N> dp, reachable;
	dp[0] = 1;
	for(int i = 0; i < n; i++) {
		dp |= dp<<nums[i];
		reachable |= dp;
		dp[i] = 0;
	}
	ll best = 0;
	ll sum = 0;
	for(int i = 0; i < 2*n; i++) {
		if(i < n)
			sum += nums[i];
		if(reachable[i])
			best = max(best, sum-i);
	}
	cout << best << "\n";
}