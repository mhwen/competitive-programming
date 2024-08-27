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
	int n;
	cin >> n;
	vector<ll> dp(500001, -1);
	dp[0] = 0;
	for(int i = 0; i < n; i++) {
		int val;
		cin >> val;
		vector<ll> next(500001, -1);
		for(int diff = 0; diff < sz(dp); diff++) {
			if(dp[diff] == -1)
				continue;
				
			//don't use
			next[diff] = max(next[diff], dp[diff]);
			
			//add to higher stack
			next[diff+val] = max(next[diff+val], dp[diff]);
			
			//add to lower stack
			if(val <= diff) {
				next[diff-val] = max(next[diff-val], dp[diff]+val);
			}
			else {
				next[val-diff] = max(next[val-diff], dp[diff]+diff);
			}
		}
		dp = next;
	}
	if(dp[0] == 0)
		cout << -1 << "\n";
	else
		cout << dp[0] << "\n";
}