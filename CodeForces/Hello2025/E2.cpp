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

constexpr int INF = 1e9+5;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, q;
		cin >> n >> m >> q;
		vector<pair<int, int>> edges(m);
		vector<int> w(m);
		vector dist(n, vector<int>(n, INF));
		for(int i = 0; i < n; i++)
			dist[i][i] = 0;
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b >> w[i];
			a--; b--;
			edges[i] = {a, b};
			dist[a][b] = dist[b][a] = 1;
		}
		
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
		
		vector<int> order(m);
		iota(all(order), 0);
		sort(all(order), [&](int a, int b) {
			return w[a] < w[b];
		});
		vector<int> p(n);
		iota(all(p), 0);
		vector<vector<int>> comp(n);
		for(int i = 0; i < n; i++)
			 comp[i].push_back(i);

		function<int(int)> getPar = [&](int a) {
			if(p[a] == a)
				return a;
			return p[a] = getPar(p[a]);
		};
		
		vector ans(n, vector(n, vector<int>(n+1, INF)));

		auto merge = [&](int a, int b) {
			a = getPar(a);
			b = getPar(b);
			if(a == b)
				return false;
			if(sz(comp[a]) > sz(comp[b]))
				swap(a, b);
			for(auto node : comp[a])
				comp[b].push_back(node);
			p[a] = b;
			return true;
		};
		
		for(auto e : order) {
			auto [a, b] = edges[e];
			if(merge(a, b)) {
				for(int i = 0; i < n; i++) {
					for(int j = 0; j < n; j++) {
						if(dist[i][a]+dist[b][j] < dist[i][j]) {
							ans[i][j][dist[i][j]] = w[e];
							dist[i][j] = dist[i][a]+dist[b][j];
						}
						if(dist[i][b]+dist[a][j] < dist[i][j]) {
							ans[i][j][dist[i][j]] = w[e];
							dist[i][j] = dist[i][b]+dist[a][j];
						}
					}
				}
			}
		}
		while(q-->0) {
			int a, b, k;
			cin >> a >> b >> k;
			a--; b--;
			cout << ans[a][b][k] << " ";
		}
		cout << "\n";
	}
}