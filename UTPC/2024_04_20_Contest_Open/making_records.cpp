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
	int n, m;
	cin >> n >> m;
	vector<int> inDegree(n);
	vector<int> next(n);
	for(int i = 0; i < n; i++) {
		cin >> next[i];
		next[i]--;
		inDegree[next[i]]++;
	}
	queue<int> q;
	for(int i = 0; i < n; i++) {
		if(inDegree[i] == 0)
			q.push(i);
	}
	ll ans = 1;
	vector<bool> vis(n);
	
	while(!q.empty()) {
		int curr = q.front();
		q.pop();
		vis[curr] = true;
		ans *= m-1;
		ans %= MOD;
		inDegree[next[curr]]--;
		if(inDegree[next[curr]] == 0)
			q.push(next[curr]);
	}
	
	function<int(int)> dfs = [&](int curr) {
		if(vis[curr])
			return 0;
		vis[curr] = true;
		return 1 + dfs(next[curr]);
	};
	
	for(int i = 0; i < n; i++) {
		if(vis[i])
			continue;
		int sz = dfs(i);
		ll ways = 1;
		for(int j = 0; j < sz; j++) {
			ways *= m-1;
			ways %= MOD;
		}
		if(sz%2)
			ways -= m-1;
		else
			ways += m-1;
			
		ways += MOD;
		ways %= MOD;
		
		ans *= ways;
		ans %= MOD;
	}
	cout << ans << "\n";
}