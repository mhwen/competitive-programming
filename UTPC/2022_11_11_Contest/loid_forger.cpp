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

bool inside(int p, int l, int r) {
	return l <= p && p <= r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> L(n);
	vector<int> R(n);
	int lowR = 1e9;
	int highL = 0;
	for(int i = 0; i < n; i++) {
		cin >> L[i] >> R[i];
		lowR = min(lowR, R[i]);
		highL = max(highL, L[i]);
	}
	vector<vector<int>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	vector<int> assignment(n, -1);
	bool good = true;
	for(int i = 0; i < n; i++) {
		bool inOne = inside(lowR, L[i], R[i]);
		bool inTwo = inside(highL, L[i], R[i]);
		if(!inOne && !inTwo)
			good = false;
		else if(!inOne && inTwo)
			assignment[i] = 1;
		else if(inOne && !inTwo)
			assignment[i] = 0;
	}
	vector<bool> vis(n);
	
	function<void(int, int)> dfs = [&](int curr, int color) {
		if(assignment[curr] != -1 && assignment[curr] != color)
			good = false;
		if(vis[curr])
			return;
		vis[curr] = true;
		assignment[curr] = color;
		for(int next : con[curr])
			dfs(next, 1-color);
	};
	
	for(int i = 0; i < n; i++) {
		if(!vis[i] && assignment[i] != -1) {
			dfs(i, assignment[i]);
		}
	}
	for(int i = 0; i < n; i++) {
		if(!vis[i]) {
			dfs(i, 1);
		}
	}
	if(good) {
		cout << "Yes\n";
		cout << lowR << " " << highL << "\n";
		for(int i : assignment)
			cout << i+1 << " ";
		cout << "\n";
	}
	else
		cout << "No\n";
}