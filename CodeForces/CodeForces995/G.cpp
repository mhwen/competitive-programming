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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, char>> events(q);
	for(int i = 0; i < q; i++) {
		cin >> events[i].first >> events[i].second;
		events[i].first--;
	}
	vector<int> dist(n, 0);
	for(auto [i, c] : events) {
		if(c == '+')
			dist[i]++;
	}
	
	auto compute = [&](int i, int j) {
		int m = 1;
		int curr = 1;
		for(auto [e, c] : events) {
			if(e == i && c == '+')
				curr++;
			if(e == j && c == '-')
				curr--;
			m = max(m, curr);
		}
		return m;
	};
	
	vector cost(n, vector<int>(n, INF));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j)
				continue;
			cost[i][j] = compute(i, j);
		}
	}
	vector dp(1<<n, vector<int>(n, INF));
	for(int i = 0; i < n; i++)
		dp[1<<i][i] = 0;
	for(int mask = 0; mask < 1<<n; mask++) {
		for(int from = 0; from < n; from++) {
			if(!(mask&(1<<from)))
				continue;
			for(int to = 0; to < n; to++) {
				if((mask&(1<<to)))
					continue;
				int newMask = mask|(1<<to);
				dp[newMask][to] = min(dp[newMask][to], dp[mask][from]+cost[from][to]);
			}
		}
	}
	int ans = INF;
	for(int i = 0; i < n; i++) {
		ans = min(ans, dp[(1<<n)-1][i]+dist[i]);
	}
	cout << ans+1 << "\n";
}