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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, s, k, g;
	cin >> n >> m >> s >> k >> g;
	s--;
	vector<vector<int>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	
	auto bfs = [&](queue<pair<int, int>> q, vector<int>& dist) {
		while(!q.empty()) {
			auto node = q.front();
			int curr = node.first;
			int d = node.second;
			q.pop();
			if(dist[curr] != INF)
				continue;
			dist[curr] = d;
			for(int next : con[curr]) {
				if(dist[next] != INF)
					continue;
				q.push({next, d+1});
			}
		}
	};
	
	vector<int> exits(k);
	for(int i = 0 ; i < k; i++) {
		cin >> exits[i];
		exits[i]--;
	}
	
	vector<int> hDist(n, INF);
	queue<pair<int, int>> hQ;
	hQ.push({s, 0});
	bfs(hQ, hDist);
	vector<int> gDist(n, INF);
	queue<pair<int, int>> gQ;
	for(int i = 0; i < g; i++) {
		int ghost;
		cin >> ghost;
		ghost--;
		gQ.push({ghost, 0});
	}
	bfs(gQ, gDist);
	int ans = 0;
	for(int e : exits) {
		if(hDist[e] < gDist[e])
			ans++;
	}
	cout << ans << "\n";
}