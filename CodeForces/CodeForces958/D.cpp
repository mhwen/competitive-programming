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

constexpr ll INF = 4e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int x, y;
			cin >> x >> y;
			x--; y--;
			con[x].push_back(y);
			con[y].push_back(x);
		}
		vector dp(n, vector<ll>(20, INF));
		vector bestWithout(n, vector<ll>(20, INF));
		function<void(int, int)> dfs = [&](int curr, int prev) {
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
			}
			for(int round = 0; round < 20; round++) {
				dp[curr][round] = (round+1)*a[curr];
				for(int next : con[curr]) {
					if(next == prev)
						continue;
					dp[curr][round] += bestWithout[next][round];
				}
			}
			vector<ll> preMin(20, INF);
			vector<ll> sufMin(20, INF);
			for(int i = 0; i < 20; i++) {
				preMin[i] = dp[curr][i];
				if(i > 0)
					preMin[i] = min(preMin[i], preMin[i-1]);
				
				sufMin[19-i] = dp[curr][19-i];
				if(i > 0)
					sufMin[19-i] = min(sufMin[19-i], sufMin[19-i+1]);
			}
			for(int i = 0; i < 20; i++) {
				if(i > 0)
					bestWithout[curr][i] = min(bestWithout[curr][i], preMin[i-1]);
				if(i < 19)
					bestWithout[curr][i] = min(bestWithout[curr][i], sufMin[i+1]);
			}
		};
		dfs(0, -1);
		cout << min(bestWithout[0][0], bestWithout[0][1]) << "\n";
	}
}