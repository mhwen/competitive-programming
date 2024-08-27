#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<ll>> dp(101, vector<ll>(10001, 1));
	for(int pow = 3; pow <= 100; pow++) {
		int p = pow;
		while(p <= 10000) {
			for(int i = 10000; i-p >= 0; i--) {
				for(int j = i-p; j >= 0; j-=p)
					dp[pow][i] += dp[pow][j];
			}
			p *= pow;
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int T, m, n;
		cin >> T >> m >> n;
		cout << T << " " << dp[m][n] << "\n";
	}
}