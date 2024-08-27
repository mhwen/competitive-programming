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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> time(3*n);
	for(int i = 0; i < n; i++) {
		cin >> time[i];
	}
	vector<vector<int>> con(3*n);
	priority_queue<pair<ll, int>> q;
	for(int i = 0; i < k; i++) {
		q.push({-time[i], i});
	}
	int id = k;
	int node = 2*n;
	ll start = -1;
	while(!q.empty() && id <= n) {
		vector<pair<ll, int>> next;
		next.push_back(q.top());
		q.pop();
		while(!q.empty() && q.top().first == next[0].first) {
			next.push_back(q.top());
			q.pop();
		}
		if(sz(next) == 1) {
			con[id].push_back(next[0].second);
			q.push({next[0].first-time[id], id});
		}
		else {
			for(int i = 0; i < sz(next); i++) {
				con[id+i].push_back(node);
				con[node].push_back(next[i].second);
				q.push({next[0].first-time[id+i], id+i});
			}
			node++;
		}
		id += sz(next);
		if(id > n)
			start = -next[0].first;
	}
	
	vector<bool> vis(3*n);
	function<void(int)> dfs = [&](int curr){
		vis[curr] = true;
		for(int next : con[curr]) {
			if(!vis[next])
				dfs(next);
		}
	};
	dfs(n);
	cout << start << "\n";
	for(int i = 0; i < k; i++)
		cout << vis[i];
	cout << "\n";
}