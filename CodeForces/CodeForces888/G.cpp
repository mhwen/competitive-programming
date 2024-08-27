#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;

typedef long long ll;
constexpr int INF = 2e9+5;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> heights(n);
		vector<vector<int>> con(n);
		for(int i = 0; i < n; i++)
			cin >> heights[i];
		for(int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
		}
		int q;
		cin >> q;
		vector<int> queryTarget(q);
		vector<bool> queryGood(q);
		vector<set<pair<int, int>>> queries(n);
		for(int i = 0; i < q; i++) {
			int a, b, e;
			cin >> a >> b >> e;
			a--; b--;
			queryTarget[i] = b;
			queries[a].insert({heights[a]+e, i});
		}
		
		vector<int> par(n);
		iota(par.begin(), par.end(), 0);
			
		function<int(int)> getParent = [&](int a) {
			if(a == par[a])
				return a;
			return par[a] = getParent(par[a]);
		};
		
		function<void(int, int)> prune = [&](int a, int val) {
			a = getParent(a);
			while(!queries[a].empty() && queries[a].begin()->first < val) {
				int qId = queries[a].begin()->second;
				if(getParent(queryTarget[qId]) == a)
					queryGood[qId] = true;
				queries[a].erase(queries[a].begin());
			}
		};
		
		function<void(int, int, int)> merge = [&](int a, int b, int val) {
			a = getParent(a);
			b = getParent(b);
			if(a == b)
				return;
			
			if((int)queries[a].size() < (int)queries[b].size())
				swap(a, b);
				
			prune(a, val);
			prune(b, val);	
			for(auto qu : queries[b])
				queries[a].insert(qu);
			par[b] = a;
		};
		
		vector<int> order(n);
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [&](int i, int j) {
			return heights[i] < heights[j];
		});
		
		for(int i : order) {
			for(int next : con[i]) {
				if(heights[next] <= heights[i])
					merge(i, next, heights[i]);
			}
		}
		for(int i = 0; i < n; i++) {
			prune(getParent(i), INF);
		}
		for(int i = 0; i < q; i++) {
			if(queryGood[i])
				cout << "YES\n";
			else
				cout << "NO\n";
		}
		cout << "\n";
	}
	

	
	
}