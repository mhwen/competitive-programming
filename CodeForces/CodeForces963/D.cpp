#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
			
		int rem = n%k;
		if(rem == 0)
			rem = k;
			
		auto check = [&](int val) {
			vector<int> dp(n, -INF);
			dp[0] = nums[0] >= val ? 1 : -1;
			for(int i = 1; i < n; i++) {
				int diff = nums[i] >= val ? 1 : -1;
				if(i%k == 0)
					dp[i] = diff;
				else
					dp[i] = dp[i-1]+diff;
				if(i-k >= 0)
					dp[i] = max(dp[i], dp[i-k]);
			}
			return dp[n-1] > 0;
		};
		
		int left = 1, right = 1e9;
		while(left <= right) {
			int mid = (left+right)/2;
			if(check(mid))
				left = mid+1;
			else
				right = mid-1;
		}
		cout << right << "\n";
	}
}