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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<int> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	vector dp(n, vector(n, vector<int>(2, INF)));
	dp[k-1][k-1][0] = 0;
	for(int len = 0; len < n; len++) {
		for(int i = 0; i+len < n; i++) {
			if(dp[i][i+len][0] < nums[i]) {
				if(i > 0)
					dp[i-1][i+len][0] = min(dp[i-1][i+len][0], dp[i][i+len][0]+1);
				if(i+len < n-1)
					dp[i][i+len+1][1] = min(dp[i][i+len+1][1], dp[i][i+len][0]+len+1);
			}
			else
				dp[i][i+len][0] = INF;
			if(dp[i][i+len][1] < nums[i+len]) {
				if(i > 0)
					dp[i-1][i+len][0] = min(dp[i-1][i+len][0], dp[i][i+len][1]+len+1);
				if(i+len < n-1)
					dp[i][i+len+1][1] = min(dp[i][i+len+1][1], dp[i][i+len][1]+1);
			}
			else
				dp[i][i+len][1] = INF;
		}
	}
	int ans = *min_element(all(dp[0][n-1]));
	if(ans == INF)
		cout << -1 << "\n";
	else
		cout << ans << "\n";
}