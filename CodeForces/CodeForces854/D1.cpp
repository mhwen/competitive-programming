#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int inputs;
	cin >> inputs;
	while(inputs-->0) {
		int n, k;
		cin >> n >> k;
		int programs[n+1];
		programs[0] = -1;
		for(int i = 0; i < n; i++) {
			cin >> programs[i+1];
		}
		ll cold[k+1];
		ll hot[k+1];
		for(int i = 0; i < k; i++) {
			cin >> cold[i+1];
		}
		for(int i = 0; i < k; i++) {
			cin >> hot[i+1];
		}
		ll dp[n+1][n+1];
		for (auto & v : dp)
   			for (auto & e : v)
      			e = 1e18;
		dp[0][0] = 0;
		dp[1][0] = cold[programs[1]];
		for(int i = 2; i <= n; i++) {
			for(int j = i-2; j >= 0; j--) {
				int curr = programs[i];
				int prev = programs[i-1];
				int otherPrev = programs[j];
				ll a = dp[i-1][j]+ ((curr == prev) ? hot[curr] : cold[curr]);
				ll b = dp[i-1][j]+ ((curr == otherPrev) ? hot[curr] : cold[curr]);
				dp[i][i-1] = min(dp[i][i-1], b);
				dp[i][j] = min(dp[i][j], a);
			}
		}
		// for (auto & v : dp) {
   			// for (auto & e : v) {
   				// cout << e << " ";
   			// }
   			// cout << "\n";
   		// }
   		// cout << "\n";
		ll best = 1e18;
		for(int i = 0; i < n; i++) {
			best = min(best, dp[n][i]);
		}
		cout << best << "\n";
	}
}