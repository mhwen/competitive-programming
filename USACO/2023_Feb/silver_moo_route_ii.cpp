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
constexpr int INF = 2e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<pair<int, int>, int>>> con(n);
	for(int i = 0; i < m; i++) {
		int from, start, to, end;
		cin >> from >> start >> to >> end;
		from--; to--;
		con[from].push_back({{start, end}, to});
	}
	for(int i = 0; i < n; i++) {
		int delay;
		cin >> delay;
		if(i == 0)
			delay = 0;
		for(auto& edge : con[i])
			edge.first.first -= delay;
		sort(con[i].begin(), con[i].end());
	}
	vector<int> dist(n, INF);
	queue<pair<int, int>> q;
	q.push({0, 0});
	while(!q.empty()) {
		auto cc = q.front();
		q.pop();
		int curr = cc.first;
		int time = cc.second;
		if(time >= dist[curr])
			continue;
		dist[curr] = time;
		while(!con[curr].empty() && time <= con[curr].back().first.first) {
			q.push({con[curr].back().second, con[curr].back().first.second});
			con[curr].pop_back();
		}
	}
	for(int i : dist) {
		if(i == INF)
			i = -1;
		cout << i << "\n";
	}
}