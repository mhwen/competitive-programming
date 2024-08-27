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
constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<pair<int, ll>>> con(n);
		vector<ll> s(n);
		for(int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			u--; v--;
			con[u].push_back({v, w});
			con[v].push_back({u, w});
		}
		for(int i = 0; i < n; i++)
			cin >> s[i];
		vector<vector<ll>> mat(n, vector<ll>(n, INF));
		function<void(int)> search = [&](int start) {
			ll cost = s[start];
			priority_queue<pair<ll, int>> q;
			q.push({0, start});
			while(!q.empty()) {
				auto c = q.top();
				q.pop();
				int curr = c.second;
				ll dist = -c.first;
				if(mat[start][curr] != INF)
					continue;
				mat[start][curr] = dist;
				for(auto next : con[curr]) {
					q.push({-(next.second*cost+dist), next.first});
				}
			}
		};
		for(int i = 0; i < n; i++)
			search(i);
		
		vector<ll> dists(n, INF);
		
		function dij = [&] {
			priority_queue<pair<ll, int>> q;
			q.push({0, 0});
			while(!q.empty()) {
				auto c = q.top();
				q.pop();
				int curr = c.second;
				ll dist = -c.first;
				if(dists[curr] != INF)
					continue;
				dists[curr] = dist;
				for(int next = 0; next < n; next++) {
					if(dists[next] != INF)
						continue;
					q.push({-(mat[curr][next]+dist), next});
				}
			}
		};
		dij();
		cout << dists[n-1] << "\n";
	}
}