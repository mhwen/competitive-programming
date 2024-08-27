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
	int n, m;
	cin >> n >> m;
	vector<ll> vals(2e5+1);
	for(int i = 0; i < n; i++) {
		string s;
		ll v;
		cin >> s >> v;
		vals[s.size()] = max(vals[s.size()], v);
	}
	vector<ll> dp(m+1);
	for(int i = 1; i <= 2e5; i++) {
		if(vals[i] == 0)
			continue;
		for(int cap = i; cap <= m; cap++) {
			dp[cap] = max(dp[cap], dp[cap-i]+vals[i]);
		}
	}
	cout << dp[m] << "\n";
}