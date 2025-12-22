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
		vector dp(m, INF);
		dp[0] = 0;

		for(int i = 0; i < n; i++) {
			vector<ll> a(m);
			vector<ll> p(m+1);
			auto query = [&](int l, int r) {
				assert(l <= r);
				assert(0 <= l && l < m);
				assert(0 <= r && r < m);
				return p[r+1]-p[l];
			};
			auto get = [&](int l, int r) {
				if(r >= m)
					return query(l, m-1)+query(0, r%m);
				else
					return query(l, r);
			};
			for(int j = 0; j < m; j++) {
				cin >> a[j];
				p[j+1] = p[j]+a[j];
			}
			vector<priority_queue<pair<ll, int>>> best(m);
			ll extra = 0;
			for(int len = 0; len < m; len++) {
				for(int j = 0; j < m; j++) {
					best[len].push({-(get(j, j+len)+k*j), j});
				}
			}
			vector<ll> newDp(m, INF);
			for(int j = 0; j < m; j++) {
				auto process = [&](int len) {
					while(true) {
						auto [val, pos] = best[len].top();
						if(pos < j) {
							best[len].pop();
							best[len].push({val-m*k, pos+m});
						}
						else
							break;
					}
				};
				for(int h = j; h < m; h++) {
					process(h-j);
					auto [val, _] = best[h-j].top();
					newDp[h] = min(newDp[h], dp[j]-val+extra);
				}
				extra -= k;
			}
			dp = newDp;
		}
		cout << dp[m-1] << "\n";
	}
}