#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int dfs(int curr, vector<bool>& vis, vector<vector<bool>>& con, vector<int>& graph) {
	vis[curr] = true;
	int degree = 0;
	graph.push_back(curr);
	for(int next = 0; next < (int)vis.size(); next++) {
		if(con[curr][next])
			degree++;
		if(!vis[next] && con[curr][next]) {
			degree += dfs(next, vis, con, graph);
		}
	}
	return degree;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<bool>> con(n, vector<bool>(n));
		vector<int> degree(n);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if(c == '1') {
					con[i][j] = true;
					degree[i]++;
				}
			}
		}
		vector<bool> vis(n);
		vector<vector<int>> components;
		int nonclique = -1;
		for(int i = 0; i < n; i++) {
			if(!vis[i]) {
				vector<int> graph;
				int d = dfs(i, vis, con, graph);
				components.push_back(graph);
				int s = (int)graph.size();
				if(s == 1 || d < s*(s-1)) {
					nonclique = (int)components.size()-1;
				}
			}
		}
		if((int)components.size() == 1) {
			cout << "0\n";
		}
		else if(nonclique != -1) {
			cout << "1\n";
			int minDeg = n;
			int minId = -1;
			for(int node : components[nonclique]) {
				if(degree[node] < minDeg) {
					minDeg = degree[node];
					minId = node;
				}
			}
			cout << minId+1 << "\n";
		}
		else if((int)components.size() > 2) {
			cout << "2\n";
			cout << components[0][0]+1 << " " << components[1][0]+1 << "\n";
		}
		else {
			
			if((int)components[0].size() > (int)components[1].size()) {
				swap(components[0], components[1]);
			}
			cout << components[0].size() << "\n";
			for(int node : components[0])
				cout << node+1 << " ";
			cout << "\n";
		}
	}
}