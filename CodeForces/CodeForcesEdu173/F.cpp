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

constexpr ll MOD = 998244353;

typedef pair<int, ll> info;

pair<info, info> upd(pair<info, info> to, info v) {
	if(v.first > to.first.first) {
		swap(to.first, to.second);
		to.first = v;
	}
	else if(v.first == to.first.first) {
		to.first.second += v.second;
		to.first.second %= MOD;
	}
	else if(v.first > to.second.first) {
		to.second = v;
	}
	else if(v.first == to.second.first) {
		to.second.second += v.second;
		to.second.second %= MOD;
	}
	return to;
}

pair<info, info> check(pair<info, info> from, pair<info, info> to, ll cnt) {
	auto [a, b] = from.first;
	auto [c, d] = from.second;
	if(b != 0)
		to = upd(to, {a+1, b*cnt%MOD});
	if(d != 0)
		to = upd(to, {c+1, d*cnt%MOD});
	return to;
}

void solve(vector<ll> cnts) {
	ll tot = 0;
	int twos = 0;
	ll twoWays = 0;
	int xr = 0;
	for(int i = 0; i <= 50; i++) {
		tot += cnts[i];
		if(cnts[i])
			xr ^= i;
		if(cnts[i] >= 2) {
			twos++;
			twoWays += cnts[i]*(cnts[i]-1)/2%MOD;
			twoWays %= MOD;
		}
	}
	if(cnts[0]) {
		if(tot > 1)
			cout << tot-1 << " " << cnts[0] << "\n";
		else
			cout << 0 << " " << 1 << "\n";
		return;
	}
	if(twos) {
		if(tot > 2)
			cout << tot-2 << " " << twoWays << "\n";
		else
			cout << 0 << " " << 1 << "\n";
		return;
	}
	
	vector<pair<info, info>> dp(64, {{0, 0}, {0, 0}});
	dp[xr] = {{0, 1}, {0, 0}};
	for(int i = 0; i <= 50; i++) {
		if(cnts[i] == 0)
			continue;
		vector<pair<info, info>> newDp = dp;
		for(int from = 0; from < 64; from++) {
			int to = from^i;
			newDp[to] = check(dp[from], newDp[to], cnts[i]);
		}
		dp = newDp;
	}
	if(dp[0].second.second != 0)
		cout << dp[0].second.first << " " << dp[0].second.second << "\n";
	else
		cout << -1 << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector cnts(n+1, vector<ll>(51));
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		cnts[i+1][a]++;
		for(int j = 0; j <= 50; j++)
			cnts[i+1][j] += cnts[i][j];
	}
	while(q-->0) {
		int l, r;
		cin >> l >> r;
		vector<ll> newCnts(51);
		for(int i = 0; i <= 50; i++)
			newCnts[i] = cnts[r][i]-cnts[l-1][i];
		solve(newCnts);
	}
}