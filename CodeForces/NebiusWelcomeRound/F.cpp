#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<pair<int, int>>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		con[a].push_back({b, 0});
		con[b].push_back({a, 0});
	}
	
	for(int i = 1; i <= q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		con[a].push_back({b, i});
		con[b].push_back({a, i});
	}
	
	vector<int> ans;
	
	function<int(int, int)> bfs = [&](int a, int level) -> int {
		if(level > q)
			return 0;
		vector<bool> vis(n);
		queue<pair<int, int>> q;
		q.push({a, 0});
		int dist = 0;
		while(!q.empty()) {
			auto curr = q.front();
			q.pop();
			vis[curr.first] = true;
			dist = max(dist, curr.second);
			for(auto next : con[curr.first]) {
				if(next.second > level)
					continue;
				if(!vis[next.first]) {
					vis[next.first] = true;
					q.push({next.first, curr.second+1});
				}
			}
		}
		return dist;
	};
	// for(int i = 0; i <= q+1; i++) {
		// cout << bfs(0, i) << " ";
	// }
	// cout << endl;
	int len = bfs(0, 0);
	int curr = 0;
	while(curr <= q) {
		int left = curr, right = q+1;
		int res = len;
		while(left < right) {
			int mid = (left+right)/2;
			res = bfs(0, mid);
			if(res*2 < len) {
				right = mid;
			}
			else {
				left = mid+1;
			}
		}
		for(int i = curr; i < left; i++) {
			ans.push_back(len);
		}
		len = res;
		// cout << curr << " " << left << " " << len << endl;
		curr = left;
	}
	for(int& i : ans)
		cout << i << " ";
	cout << "\n";
	
}