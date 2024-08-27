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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<vector<int>> dp(2, vector<int>(n));
		function<void(int, int)> dfs = [&](int curr, int prev) {
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
			}
			dp[1][curr] = 1;
			
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dp[0][curr] += max(dp[0][next], dp[1][next]);
				dp[1][curr] += dp[0][next];
			}
		};
		dfs(0, -1);
		int ans = 0;
		function<void(int, int, int, int)> reroot = [&](int curr, int prev, int yes, int no) {
			int myYes = dp[1][curr]+no;
			int myNo = dp[0][curr]+max(yes, no);
			int res = max(myYes, myNo);
			if(sz(con[curr]) == 1)
				res = max(myYes, myNo+1);
			ans = max(ans, res);
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				int newYes = myYes-dp[0][next];
				int newNo = myNo-max(dp[0][next], dp[1][next]);
				reroot(next, curr, newYes, newNo);
			}
		};
		
		reroot(0, -1, 0, 0);
		cout << ans << "\n";
		
	}
}