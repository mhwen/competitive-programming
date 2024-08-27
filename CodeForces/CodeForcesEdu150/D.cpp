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
		vector<pair<int, int>> intervals(n);
		vector<int> ends(n);
		for(int i = 0; i < n; i++) {
			int l, r;
			cin >> l >> r;
			intervals[i] = {r, l};
			ends[i] = r;
		}
		sort(intervals.begin(), intervals.end());
		sort(ends.begin(), ends.end());
		vector<int> dp(n+1, 1e9);
		dp[0] = 0;
		for(int i = 0; i < n; i++) {
			dp[i+1] = dp[i]+1;
			for(int j = i-1; j >= 0; j--) {
				if(intervals[j].first < intervals[i].second)
					break;
				auto prev = lower_bound(ends.begin(), ends.end(), min(intervals[j].second, intervals[i].second));
				int prevIndex = (int)(prev-ends.begin());
				dp[i+1] = min(dp[i+1], dp[prevIndex]+i-prevIndex-1);
			}
		}
		cout << dp[n] << "\n";
	}
}