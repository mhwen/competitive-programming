#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	vector<int> sizes(n);
	vector<int> largest(n);
	function<void(int, int)> dfs = [&](int curr, int prev) {
		sizes[curr] = 1;
		for(int next : con[curr]) {
			if(next == prev)
				continue;
			dfs(next, curr);
			sizes[curr] += sizes[next];
			largest[curr] = max(largest[curr], sizes[next]);
		}
	};
	dfs(0, -1);
	cout << sizes[0] - largest[0] << "\n";
}