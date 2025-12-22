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

ll bpow(ll a, ll b) {
	ll res = 1;
	ll p = a;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b/=2;
	}
	return res;
}

ll inv(ll a) {
	return bpow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int x, y;
			cin >> x >> y;
			x--; y--;
			con[x].push_back(y);
			con[y].push_back(x);
		}
		vector<ll> escape(n);
		escape[0] = 0;
		escape[1] = inv(2);
		for(int i = 2; i < n; i++) {
			ll bot = (1-inv(2)*escape[i-1]%MOD+MOD)%MOD;
			escape[i] = inv(2)*inv(bot)%MOD;
		}
		vector<int> p(n, -1);
		
		vector<int> fromLeaf(n);
		vector<int> order;
		function<void(int, int)> dfs = [&](int curr, int prev) {
			order.push_back(curr);
			p[curr] = prev;
			int dist = n;
			for(auto next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
				dist = min(dist, fromLeaf[next]+1);
			}
			if(dist == n)
				dist = 0;
			fromLeaf[curr] = dist;
		};
		dfs(0, -1);
		
		vector<ll> win(n);
		win[0] = 1;
		for(auto curr : order) {
			if(curr == 0)
				continue;
			win[curr] = escape[fromLeaf[curr]]*win[p[curr]]%MOD;
		}
		for(auto a : win)
			cout << a << " ";
		cout << "\n";
	}
}