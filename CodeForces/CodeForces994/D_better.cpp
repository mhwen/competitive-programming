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

constexpr ll INF = 4e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		ll k;
		cin >> n >> m >> k;
		vector<ll> dp(m, INF);
		dp[0] = 0;
		for(int i = 0; i < n; i++) {
			vector shift(m, vector<ll>(m, INF));
			vector<ll> a(m);
			for(int j = 0; j < m; j++)
				cin >> a[j];
			vector<ll> newDp(m, INF);
			for(int s = 0; s < m; s++) {
				for(int j = 0; j < m; j++) {
					shift[s][j] = dp[j]+k*s;
					if(j > 0)
						shift[s][j] = min(shift[s][j], shift[s][j-1]);
					shift[s][j] += a[(j+s)%m];
					newDp[j] = min(newDp[j], shift[s][j]);
				}
			}
			dp = newDp;
		}
		cout << dp[m-1] << "\n";
	}
}