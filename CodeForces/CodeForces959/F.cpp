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
typedef pair<int, int> pii;
typedef vector<int> vi;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

vi eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> degree(n);
		vector<vector<int>> con(n);
		int edgeId = 0;
		vector<vector<pii>> edges(n);
		
		for(int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--;
			if(c == 0) {
				con[a].push_back(b);
				con[b].push_back(a);
			}
			else {
				degree[a]++;
				degree[b]++;
				edges[a].push_back({b, edgeId});
				edges[b].push_back({a, edgeId});
				edgeId++;
			}
		}
		vector<bool> vis(n);
		function<int(int, int)> dfs = [&](int curr, int prev) {
			vis[curr] = true;
			int myCount = degree[curr]%2;
			for(int next : con[curr]) {
				if(next == prev || vis[next])
					continue;
				int count = dfs(next, curr);
				if(count%2==1) {
					edges[curr].push_back({next, edgeId});
					edges[next].push_back({curr, edgeId});
					edgeId++;
				}
				myCount += count;
			}
			return myCount;
		};
		for(int i = 0; i < n; i++) {
			if(!vis[i])
				dfs(i, -1);
		}
		auto path = eulerWalk(edges, edgeId, 0);
		if(path.empty())
			cout << "NO\n";
		else {
			cout << "YES\n";
			cout << sz(path)-1 << "\n";
			for(int i : path)
				cout << i+1 << " ";
			cout << "\n";
		}
	}
}