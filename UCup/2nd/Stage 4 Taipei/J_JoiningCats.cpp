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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> cats(n);
	vector<ll> winds(k);
	vector<ll> preSum(n+1);
	vector<ll> sufSum(n+1);
	for(int i = 0; i < n; i++) {
		cin >> cats[i];
		preSum[i+1] = preSum[i]+cats[i];
	}
	for(int i = n-1; i >= 0; i--) {
		sufSum[i] = sufSum[i+1]+cats[i];
	}
	reverse(sufSum.begin(), sufSum.end());
	
	for(int i = 0; i < k; i++) {
		cin >> winds[i];
	}
	reverse(winds.begin(), winds.end());
	//longest suffix i can make with prefix p and winds w
	vector<vector<int>> dp(n+1, vector<int>(k+1, -1));
	dp[0][0] = 0;
	for(int p = 0; p <= n; p++) {
		for(int w = 1; w <= k; w++) {
			ll wind = winds[w-1];
			//use it on prefix
			// preSum[p]-preSum[i-1] <= wind
			// preSum[p]-wind <= preSum[i-1]
			ll pSum = preSum[p]-wind;
			int oldP = (int)(lower_bound(preSum.begin(), preSum.end(), pSum)-preSum.begin());
			dp[p][w] = max(dp[p][w], dp[oldP][w-1]);
			//use it on suffix
			// sufSum[s] - sufSum[oldS] <= wind
			// sufSum[s] <= sufSum[oldS] + wind
			int oldSuf = dp[p][w-1];
			if(oldSuf == -1)
				continue;
			ll sSum = sufSum[oldSuf]+wind;
			int newS = (int)(upper_bound(sufSum.begin(), sufSum.end(), sSum)-sufSum.begin())-1;
			dp[p][w] = max(dp[p][w], newS);
			// cout << p << " " << w << " " << dp[p][w] << endl;
		}
	}
	bool pos = false;
	for(int i = 1; i <= n; i++) {
		// cout << i << " " << dp[i-1][k] << endl;
		if(dp[i-1][k] >= n-i)
			pos = true;
	}
	if(pos)
		cout << "Yes\n";
	else
		cout << "No\n";
}