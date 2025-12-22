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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		vector<vector<int>> seen(n+1);
		vector<int> dp(n+1);
		for(int i = 0; i < n; i++) {
			dp[i+1] = dp[i];
			seen[a[i]].pb(i);
			int s = sz(seen[a[i]]);
			if(s >= a[i])
				dp[i+1] = max(dp[i+1], dp[seen[a[i]][s-a[i]]]+a[i]);
		}
		cout << dp.back() << "\n";
	}
}