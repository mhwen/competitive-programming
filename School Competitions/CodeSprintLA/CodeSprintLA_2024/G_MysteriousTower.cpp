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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	//expected value of sequences with extra open brackets
	vector<vector<ld>> dp(n+1, vector<ld>(n+1));
	vector<vector<ld>> pos(n+1, vector<ld>(n+1));
	pos[0][0] = 1;
	
	vector<ld> probs(n+1);
	for(int i = 1; i <= n; i++) {
		cin >> probs[i];
	}
	
	for(int i = 1; i <= n; i++) {
		ld up = probs[i];
		ld down = 1-up;
		for(int extra = 0; extra < n; extra++) {
			pos[i][extra+1] += up*pos[i-1][extra];
			if(extra == 0)
				pos[i][extra] += down*pos[i-1][extra];
			else
				pos[i][extra-1] += down*pos[i-1][extra];
		}
	}
	
	for(int i = 1; i <= n; i++) {
		ld up = probs[i];
		ld down = 1-up;
		for(int extra = 0; extra < n; extra++) {
			if(pos[i-1][extra] == 0)
				continue;

			//add (
			if(pos[i][extra+1] != 0)
				dp[i][extra+1] += up*pos[i-1][extra]/pos[i][extra+1]*(1+dp[i-1][extra]);
			
			//add )
			if(extra == 0) {
				if(pos[i][extra] != 0)
					dp[i][extra] += down*pos[i-1][extra]/pos[i][extra]*dp[i-1][extra];
			}
			else {
				if(pos[i][extra-1] != 0)
					dp[i][extra-1] += down*pos[i-1][extra]/pos[i][extra-1]*(1+dp[i-1][extra]);
			}
		}
	}
	ld ans = 0;
	for(int i = 0; i <= n; i++) {
		ans += (dp[n][i]-i)*pos[n][i];
	}
	cout << setprecision(20) << ans << "\n";
}