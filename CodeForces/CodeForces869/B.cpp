#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> con(n);
		vector<int> degree(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
			degree[a]++;
			degree[b]++;
		}
		bool found = false;
		for(int i = 0; i < n; i++) {
			if(degree[i] < 4)
				continue;
			for(int j : con[i]) {
				vector<int> parent(n, -1);
				queue<pair<int, int>> queue;
				queue.push({i, j});
				bool reached = false;
				while(!queue.empty()) {
					auto curr = queue.front();
					queue.pop();
					int id = curr.first;
					int par = curr.second;
					if(parent[id] != -1)
						continue;
					parent[id] = par;
					if(id == j) {
						reached = true;
						break;
					}
					for(int next : con[id]) {
						if(next == par)
							continue;
						queue.push({next, id});
					}
				}
				if(reached) {
					vector<pair<int, int>> ans;
					
					int curr = j;
					set<int> used;
					ans.push_back({i, j});
					while(curr != i) {
						used.insert(curr);
						ans.push_back({curr, parent[curr]});
						curr = parent[curr];
					}
					int k = (int)ans.size();
					for(int next : con[i]) {
						if(used.count(next) == 0) {
							ans.push_back({i, next});
							if((int)ans.size() == k+2) {
								break;
							}
						}
					}
					cout << "YES\n";
					cout << k+2 << "\n";
					for(auto a : ans) {
						cout << a.first+1 << " " << a.second+1 << "\n";
					}
					found = true;
					goto A;

				}
			}
		}
		A:
		if(!found)
			cout << "NO\n";
	}
}