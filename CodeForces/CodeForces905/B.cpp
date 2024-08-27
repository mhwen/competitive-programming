#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, t;
	cin >> n >> t;
	vector<vector<pair<int, int>>> con(n);

	for(int i = 1; i <= t; i++) {
		int m;
		cin >> m;
		for(int j = 0; j < m; j++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back({i, b});
			con[b].push_back({i, a});
		}
	}
	int k;
	cin >> k;
	vector<int> eras(k);
	vector<set<int>> occurrences(t+1);
	for(int i = 0; i < k; i++) {
		cin >> eras[i];
		occurrences[eras[i]].insert(i);
	}
	vector<int> vis(n, INF);
	priority_queue<pair<int, int>> q;
	q.push({0, 0});
	int ans = -1;
	while(!q.empty()) {
		auto curr = q.top();
		q.pop();
		int time = -curr.first;
		int node = curr.second;
		if(time >= vis[node])
			continue;
		vis[node] = time;
		if(node == n-1) {
			ans = time;
			break;
		}
		for(auto next : con[node]) {
			int nextEra = next.first;
			int nextNode = next.second;
			auto it = occurrences[nextEra].lower_bound(time);
			if(it == occurrences[nextEra].end())
				continue;
			int nextTime = *it;
			if(vis[nextNode] > nextTime+1) {
				q.push({-nextTime-1, nextNode});
			}
		}
	}
	cout << ans << "\n";
	
}