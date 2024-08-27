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
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> costs(n);
	ll pow = 1;
	costs[1] = pow;
	for(int i = 2; i < n; i++) {
		pow = pow*3%MOD;
		costs[i] = (costs[i-1]+pow)%MOD;
	}
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	
	function<int(int, int)> dfs = [&](int curr, int prev) -> int {
		int sz = 1;
		for(int next : con[curr]) {
			if(next == prev)
				continue;
			sz += dfs(next, curr);
		}
		return sz;
	};
	ll ans = 0;
	for(int subTrees : con[0]) {
		ans = (ans+costs[dfs(subTrees, 0)])%MOD;
	}
	cout << ans << "\n";
		
}