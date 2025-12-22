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
		for(int i = 0; i < l; i++)
			cin >> a[i];
		vector<vector<int>> grid(n, vector<int>(m));
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				cin >> grid[r][c];
			}
		}
		vector<vector<int>> dp(n+1, vector<int>(m+1));
		auto process = [&](int val) {
			vector<vector<int>> newDp(n+1, vector<int>(m+1));
			for(int r = 0; r < n; r++) {
				for(int c = 0; c < m; c++) {
					if(grid[r][c] == val) {
						int wins = dp[r+1][c+1];
						if(wins == 0)
							newDp[r][c] = 1;
					}
				}
			}
			for(int r = n-1; r >= 0; r--) {
				for(int c = m-1; c >= 0; c--) {
					newDp[r][c] += newDp[r+1][c]+newDp[r][c+1]-newDp[r+1][c+1];
				}
			}
			return newDp;
		};
		for(int i = l-1; i >= 0; i--) {
			dp = process(a[i]);
		}
		bool win = false;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(dp[r][c])
					win = true;
			}
		}
		if(win)
			cout << "T\n";
		else
			cout << "N\n";
	}
}