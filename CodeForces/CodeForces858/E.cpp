#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace std;

typedef long long ll;

const int sqrtn = 325;

vector<vector<ll>> seen(1e5+1, vector<ll>(sqrtn));
vector<ll> nums(1e5+1);
vector<int> p(1e5+1);
vector<vector<int>> children(1e5+1);
vector<int> depth(1e5+1);
vector<int> cnt(1e5+1);
vector<int> id(1e5+1);

void dfs(int curr, int d) {
	id[curr] = ++cnt[d];
	depth[curr] = d;
	for(auto next : children[curr]) {
		dfs(next, d+1);
	}
}

ll solve(int x, int y) {
	if(x == 0 && y == 0)
		return 0ll;
	if(x > y)
		swap(x, y);
	if(cnt[depth[y]] < sqrtn && seen[x][id[y]])
		return seen[x][id[y]];
	ll ans = nums[x]*nums[y]+solve(p[x], p[y]);
	if(cnt[depth[y]] < sqrtn)
		seen[x][id[y]] = ans;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	p[0] = p[1] = 0;
	for(int i = 2; i <= n; i++) {
		cin >> p[i];
		children[p[i]].push_back(i);
	}
	
	dfs(1, 0);
	
	for(int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		cout << solve(x, y) << "\n";
	}
}