#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T-->0) {
		ll a, b, m;
		cin >> a >> b >> m;
		vector<ll> dp(m+1, -1);
		dp[0] = 2;
		ll best = 0;
		ll waitTime = (b+a-1)/a*a;
		for(int t = 0; t <= m; t++) {
			if(dp[t] == -1)
				continue;
				
			//immediate
			if(t+b <= m) {
				dp[t+b] = max(dp[t+b], dp[t]+b/a+1);
			}
			else {
				best = max(best, dp[t]+(m-t)/a);
			}
			
			//wait
			if(t+waitTime <= m) {
				dp[t+waitTime] = max(dp[t+waitTime], dp[t]+(b+a-1)/a+1);
			}
			else {
				best = max(best, dp[t]+(m-t)/a);
			}
		}
		cout << best*160 << "\n";
	}
}