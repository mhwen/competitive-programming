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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int i = 0; i < n; i++) 
			cin >> nums[i];
		ll ans = 0;
		vector<ll> dp(n+1);
		vector<map<int, int>> next(n+1);
		for(int i = n-1; i >= 0; i--) {
			if(next[i+1].count(nums[i]) != 0) {
				int Next = next[i+1][nums[i]];
				dp[i] = 1+dp[Next+1];
				ans += dp[i];
				swap(next[Next+1], next[i]);
			}
			next[i][nums[i]] = i;
		}
		cout << ans << "\n";
	}
}