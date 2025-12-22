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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("lazy.in");
	ofstream cout("lazy.out");
	int n, k;
	cin >> n >> k;
	vector grid(2*n, vector<int>(2*n));
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			cin >> grid[r+c][c-r+n];
		}
	}
	vector p(2*n+1, vector<int>(2*n+1));
	int ans = 0;
	int K = 2*k+1;
	for(int r = 1; r < 2*n+1; r++) {
		for(int c = 1; c < 2*n+1; c++) {
			p[r][c] = p[r-1][c]+p[r][c-1]-p[r-1][c-1]+grid[r-1][c-1];
			if((r+c)%2==n%2) {
				int res = p[r][c];
				if(r >= K)
					res -= p[r-K][c];
				if(c >= K)
					res -= p[r][c-K];
				if(r >= K && c >= K)
					res += p[r-K][c-K];
				ans = max(ans, res);
			}
		}
	}
	cout << ans << "\n";
}