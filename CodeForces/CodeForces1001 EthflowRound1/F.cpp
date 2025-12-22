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
#define pb push_back

constexpr ll INF = 1e18;

void chmin(ll& v, ll a) {
	v = min(v, a);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a(n), b(n), x(n), y(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i] >> b[i];
			a[i] *= 2;
			b[i] *= 2;
			x[i] = (a[i]+b[i])/2;
			y[i] = (a[i]-b[i])/2;
		}
		vector<int> order(n);
		iota(all(order), 0);
		sort(all(order), [&](int i, int j) {
			return y[i] < y[j];
		});
		vector<ll> ans(n+1, INF);
		vector dp(n+1, vector<ll>(4, INF));
		dp[0][0] = 0;
		for(int id = 0; id < n; id++) {
			int i = order[id];
			vector newDp = dp;
			chmin(newDp[1][0], dp[0][0]+2*x[i]-2*y[i]);
			chmin(newDp[1][1], dp[0][0]+2*x[i]-2*y[i]-a[i]);
			chmin(newDp[1][2], dp[0][0]+2*x[i]-2*y[i]-b[i]);
			for(int len = 2; len <= n; len++) {
				vector<ll>& curr = newDp[len];
				vector<ll>& prev = dp[len-1];
				for(int mask = 0; mask < 4; mask++)
					chmin(curr[mask], prev[mask]+2*x[i]);
				chmin(curr[1], prev[0]+2*x[i]-a[i]);
				chmin(curr[2], prev[0]+2*x[i]-b[i]);
				chmin(curr[3], prev[1]+2*x[i]-b[i]);
				chmin(curr[3], prev[2]+2*x[i]-a[i]);
				chmin(ans[len], curr[3]+2*y[i]);
			}
			swap(newDp, dp);
		}
		for(int len = 2; len <= n; len++)
			cout << ans[len]/2 << " ";
		cout << "\n";
	}
}