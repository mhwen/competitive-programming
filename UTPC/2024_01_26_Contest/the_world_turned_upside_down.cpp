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
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	sort(nums.begin(), nums.end());
	int best = 0;
	vector<int> dp(n);
	for(int i = 0; i < n; i++) {
		dp[i] = 1;
		for(int j = 0; j < i; j++) {
			if(nums[i]%nums[j]==0)
				dp[i] = max(dp[i], dp[j]+1);
		}
		best = max(best, dp[i]);
	}
	cout << best << "\n";
}