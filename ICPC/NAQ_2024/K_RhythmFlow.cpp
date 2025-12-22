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
	int n, m;
	cin >> n >> m;
	vector<ll> dp(n);
	vector<ll> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}	
	for(int i = 0; i < m; i++) {
		ll me;
		cin >> me;
		for(int j = n-1; j >= 0; j--) {
			ll score = (j == 0) ? 0 : dp[j-1];
			ll dist = abs(me-a[j]);
			if(dist <= 15)
				score += 7;
			else if(dist <= 23)
				score += 6;
			else if(dist <= 43)
				score += 4;
			else if(dist <= 102)
				score += 2;
			dp[j] = max(dp[j], score);
		}
		for(int j = 1; j < n; j++)
			dp[j] = max(dp[j], dp[j-1]);
	}
	cout << *max_element(all(dp)) << "\n";
}