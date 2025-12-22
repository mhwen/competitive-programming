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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int l, n, m;
		cin >> l >> n >> m;
		vector<int> a(l);
		set<int> seen;
		for(int i = 0; i < l; i++) {
			cin >> a[i];
			seen.insert(a[i]);
		}
		vector<int> coords(sz(seen));
		int I = 0;
		for(auto s : seen)
			coords[I++] = s;
		auto comp = [&](int val) {
			return (int)(lower_bound(all(coords), val)-coords.begin());
		};
		vector<vector<int>> grid(n, vector<int>(m));
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++)
				cin >> grid[r][c];
		}
		vector<vector<int>> rem(sz(seen), vector<int>(m, -1));
		vector<vector<int>> dp(l, vector<int>(m, -1));
		for(int c = 0; c < m; c++) {
			for(int r = 0; r < n; r++) {
				int val = grid[r][c];
				if(seen.count(val)) {
					val = comp(val);
					if(val == sz(seen)-1)
						dp[l-1][c] = r;
					rem[val][c] = r;
				}
			}
		}
		for(int i = l-2; i >= 0; i--) {
			int h = -1;
			int currNum = comp(a[i]);
			for(int c = m-1; c >= 0; c--) {
				if(rem[currNum][c] >= h)
					dp[i][c] = rem[currNum][c];
				h = max(h, dp[i+1][c]);
			}
		}
		bool win = false;
		for(int c = 0; c < m; c++)
			if(dp[0][c] >= 0)
				win = true;
		if(win)
			cout << "T\n";
		else
			cout << "N\n";
	}
}