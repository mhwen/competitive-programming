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

constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<vector<ll>> costs(n+1, vector<ll>(n+1));
	for(int r = 1; r <= n; r++) {
		for(int c = 1; c <= n; c++) {
			char C;
			cin >> C;
			costs[r][c] = C-'0';
			costs[r][c] += costs[r][c-1]+costs[r-1][c]-costs[r-1][c-1];
		}
	}
	auto getCost = [&](int l, int r) {
		return (costs[r][r]-costs[r][l-1]-costs[l-1][r]+costs[l-1][l-1])/2;
	};
	vector<ll> dp(n+1, INF);
	vector<ll> newDp(n+1, INF);
	dp[0] = 0;
	vector<int> opt(n+1);
	function<void(int, int, int, int)> solveLayer = [&](int l, int r, int lBound, int rBound) {
		if(r < l)
			return;
		int mid = (l+r)/2;
		for(int i = lBound; i <= min(mid, rBound); i++) {
			ll cost = dp[i-1]+getCost(i, mid);
			if(cost < newDp[mid]) {
				newDp[mid] = cost;
				opt[mid] = i;
			}
		}
		solveLayer(l, mid-1, lBound, opt[mid]);
		solveLayer(mid+1, r, opt[mid], rBound);
	};
	for(int i = 1; i <= k; i++) {
		solveLayer(1, n, 1, n);
		dp = newDp;
	}
	cout << dp[n] << "\n";
}