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
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<vector<ll>> dp(2, vector<ll>(n+1));
		dp[1][n-1] = max(0, nums[n-1]);
		for(int i = n-2; i >= 0; i--) {
			dp[1][i] = max(dp[1][i], dp[0][i+1]);
			dp[1][i] = max(dp[1][i], nums[i]+dp[1][i+1]);
			dp[1][i] = max(dp[1][i], max(0, nums[i])+max(dp[1][i+2], dp[0][i+2]));
			dp[0][i] = max(dp[0][i], dp[0][i+1]);
			dp[0][i] = max(dp[0][i], dp[1][i+1]);
		}
		cout << dp[1][0] << "\n";
	}
}