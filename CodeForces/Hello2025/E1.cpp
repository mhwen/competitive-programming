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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, q;
		cin >> n >> m >> q;
		vector<int> weights;
		vector<vector<pair<int, int>>> con(n);
		for(int i = 0; i < m; i++) {
			int a, b, w;
			cin >> a >> b >> w;
			a--; b--;
			con[a].push_back({b, w});
			con[b].push_back({a, w});
			weights.push_back(w);
		}
		sort(all(weights));
		weights.erase(unique(all(weights)), weights.end());
		vector res(n, vector(n, vector<int>(sz(weights))));
		
		auto bfs = [&](int start, int maxWId) {
			int maxW = weights[maxWId];
			deque<pair<int, int>> qu;
			vector<int> vis(n, m+5);
			qu.push_back({start, 0});
			vis[start] = 0;
			while(!qu.empty()) {
				auto [curr, dist] = qu.front();
				qu.pop_front();
				if(vis[curr] < dist)
					continue;
				for(auto [next, w] : con[curr]) {
					if(w > maxW && vis[next] > dist+1) {
						vis[next] = dist+1;
						qu.push_back({next, dist+1});
					}
					else if(w <= maxW && vis[next] > dist) {
						vis[next] = dist;
						qu.push_front({next, dist});
					}
				}
			}
			for(int i = 0; i < sz(vis); i++)
				res[start][i][sz(weights)-1-maxWId] = vis[i];
		};
		
		for(int i = 0; i < n; i++) {
			for(int w = 0; w < sz(weights); w++)
				bfs(i, w);
		}
		reverse(all(weights));
		
		while(q-->0) {
			int a, b, k;
			cin >> a >> b >> k;
			a--; b--;
			int id = (int)(upper_bound(all(res[a][b]), k-1)-res[a][b].begin())-1;
			cout << weights[id] << " ";
		}
		cout << "\n";
		
	}
}