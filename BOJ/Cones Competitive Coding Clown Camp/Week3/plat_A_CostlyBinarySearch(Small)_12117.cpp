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

int solve(string& s) {
	int n = sz(s);
	vector left(10, vector<int>(n+1, -1));
	for(int i = 0; i <= n; i++) {
		if(i > 0)
			for(int val = 1; val <= 9; val++)
				left[val][i] = left[val][i-1];
		if(i < n)
			left[s[i]-'0'][i] = i;
	}
	vector dp(9*14+1, vector<int>(n+2));
	int ans = 1e9;
	for(int cost = 1; cost < sz(dp); cost++) {
		for(int i = 0; i < n; i++) {
			for(int val = 1; val <= min(9, cost); val++) {
				int id = left[val][i+dp[cost-val][i]];
				if(id < i)
					continue;
				dp[cost][i] = max(dp[cost][i], id-i+1+dp[cost-val][id+1]);
			}
		}
		if(dp[cost][0] == n) {
			ans = cost;
			break;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	for(int ca = 1; ca <= t; ca++) {
		string s;
		cin >> s;
		cout << "Case #" << ca << ": " << solve(s) << "\n";
	}
}