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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	
	vector<bool> seen(k);
	vector<vector<int>> con(k);
	vector<int> degree(k);
	vector<bool> sawDouble(k);
	set<pair<int, int>> edges;
	for(int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		if(a > b)
			swap(a, b);
		edges.insert({a, b});
	}
	
	for(auto [a, b] : edges) {
		seen[a] = true;
		seen[b] = true;
		//aa
		if(a == b) {
			sawDouble[a] = true;
			continue;
		}
		//ab
		con[a].push_back(b);
		con[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}
	
	vector<int> vis(k);
	//0 not vis
	//1 in path
	//2 done vis
	function<bool(int, int)> dfs = [&](int curr, int prev) {
		vis[curr] = 1;
		bool cycleFound = false;
		for(int next : con[curr]) {
			if(next == prev)
				continue;
			if(vis[next] == 2)
				continue;
			else if(vis[next] == 1)
				cycleFound = true;
			else
				cycleFound |= dfs(next, curr);
		}
		vis[curr] = 2;
		return cycleFound;

	};
	
	int components = 0;
	bool cycle = false;
	for(int i = 0; i < k; i++) {
		if(!seen[i])
			continue;
		if(vis[i] == 2)
			continue;
		components++;
		cycle |= dfs(i, -1);
	}
	
	auto checkDegrees = [&]() {
		vector<int> bad;
		for(int i = 0; i < k; i++) {
			if(degree[i] == 1 && !sawDouble[i]) {
				bad.push_back(i);
			}
		}
		for(int b : bad) {
			degree[con[b].back()]--;
			degree[b]--;
		}
		for(int i = 0; i < k; i++) {
			if(degree[i] > 2)
				return false;
		}
		return true;
	};
	
	bool win = checkDegrees();
	if(cycle && components > 1)
		win = false;
	// cout << cycle << " " << components << endl;
	if(win) {
		cout << "possible\n";
	}
	else {
		cout << "impossible\n";
	}
	
}