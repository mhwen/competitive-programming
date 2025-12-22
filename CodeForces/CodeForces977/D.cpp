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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<ll>> grid(n, vector<ll>(m));
		for(int r = 0; r < n ; r++) {
			for(int c = 0; c < m; c++) {
				cin >> grid[r][c];
			}
		}
		vector<ll> left(m);
		vector<ll> right(m);
		
		auto prefix = [&](vector<ll>& row) {
			vector<ll> p(m, 0);
			p[0] = INF;
			ll sum = 0;
			for(int c = 0; c < m-2; c++) {
				sum += row[c];
				p[c+2] = min(p[c+1], sum);
			}
			return p;
		};
		auto suffix = [&](vector<ll>& row) {
			vector<ll> p(m, 0);
			p[m-1] = INF;
			ll sum = 0;
			for(int c = m-1; c >= 2; c--) {
				sum += row[c];
				p[c-2] = min(p[c-1], sum);
			}
			return p;
		};
		
		ll best = 0;
		for(int c = 0; c < m; c++) {
			best += grid[0][c];
			best = max(best, grid[0][c]);
			right[c] = best;
		}
		best = 0;
		for(int c = m-1; c >= 0; c--) {
			best += grid[0][c];
			best = max(best, grid[0][c]);
			left[c] = best;
		}
		for(int r = 1; r < n; r++) {
			vector<ll> newRight(m, -INF);
			vector<ll> newLeft(m, -INF);
			auto p = prefix(grid[r]);
			auto s = suffix(grid[r]);
			ll sum = grid[r][0];
			for(int c = 1; c < m; c++) {
				sum += grid[r][c];
				newRight[c] = max(newRight[c], newRight[c-1]+grid[r][c]);
				newRight[c] = max(newRight[c], right[c-1]+sum-p[c]);
				newRight[c] = max(newRight[c], left[c]+sum-p[c]);
			}
			sum = grid[r][m-1];
			for(int c = m-2; c >= 0; c--) {
				sum += grid[r][c];
				newLeft[c] = max(newLeft[c], newLeft[c+1]+grid[r][c]);
				newLeft[c] = max(newLeft[c], left[c+1]+sum-s[c]);
				newLeft[c] = max(newLeft[c], right[c]+sum-s[c]);
			}
			left = newLeft;
			right = newRight;
		}
		cout << max(*max_element(all(left)), *max_element(all(right))) << "\n";
	}
}