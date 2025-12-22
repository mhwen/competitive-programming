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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> dp(2, vector<int>(m+1));
	int best = 0;
	for(int i = 0; i < n; i++) {
	    int w, v;
	    cin >> w >> v;
	    for(int c = m; c >= 0; c--) {
	        dp[1][c] = max(dp[1][c], dp[0][c]+v);
	        if(c-w >= 0) {
    	        dp[0][c] = max(dp[0][c], dp[0][c-w]+v);
    	        dp[1][c] = max(dp[1][c], dp[1][c-w]+v);
    	    }
    	    best = max(best, max(dp[0][c], dp[1][c]));
	    }
	}
	cout << best << "\n";
}