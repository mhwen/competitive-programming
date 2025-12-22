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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
	ll res = 1;
	ll pow = a;
	while(b > 0) {
		if(b%2)
			res = res*pow%MOD;
		pow = pow*pow%MOD;
		b >>= 1;
	}
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	
	vector<ll> fact(2e5);
	vector<ll> invFact(2e5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	auto choose = [&](int a, int b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	for(int ca = 1; ca <= t; ca++) {
		int n;
		cin >> n;
		stack<int> s;
		vector<vector<int>> con(n+1);
		s.push(0);
		bool good = true;
		for(int i = 1; i <= n; i++) {
			int m;
			cin >> m;
			if(m > sz(s))
				good = false;
			int prev = -1;
			while(sz(s) > m) {
				prev = s.top();
				s.pop();
			}
			if(prev != -1) {
				con[s.top()].pop_back();
				con[i].push_back(prev);
			}
			con[s.top()].push_back(i);
			s.push(i);
		}
		vector<int> sizes(n+1);
		vector<ll> dp(n+1, 1);
		
		function<void(int)> solve = [&](int curr) {
			int childSize = 0;
			for(int next : con[curr]) {
				solve(next);
				childSize += sizes[next];
				dp[curr] = dp[curr]*dp[next]%MOD;
			}
			sizes[curr] = 1+childSize;
			for(int next : con[curr]) {
				dp[curr] = dp[curr]*choose(childSize, sizes[next])%MOD;
				childSize -= sizes[next];
			}
		};
		ll ans = good ? (solve(0), dp[0]) : 0;
		cout << "Case #" << ca << ": " << ans << "\n";;
	}
}