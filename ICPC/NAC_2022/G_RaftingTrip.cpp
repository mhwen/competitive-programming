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

//11:12
//12:08 finish

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};
char dir[4] = {'>', '<', '^', 'v'};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for(int r = 0; r < n; r++)
		cin >> grid[r];
	auto getId = [&](int r, int c) {
		return r*m+c;
	};
	auto out = [&](int r, int c) {
		return r < 0 || c < 0 || r >= n || c >= m;
	};
	auto water = [&](int r, int c) {
		return !out(r, c) && grid[r][c] != '#' && grid[r][c] != '.';
	};
	vector<vector<int>> con(n*m);
	vector<vector<int>> par(20, vector<int>(n*m, -1));
	vector<int> dep(n*m, -1);
	vector<int> vis(n*m);
	
	
	vector<int> cycle(n*m, -1);

	auto getEntryPoint = [&](int id) {
		if(cycle[id] != -1) {
			return cycle[id];
		}
		return id;
	};
	
	int cycleId = -1;
	
	function<void(int, int)> dfs = [&](int r, int c) {
		int id = getId(r, c);
		vis[id] = 1;
		for(int d = 0; d < 4; d++) {
			if(grid[r][c] == dir[d]) {
				int newR = r+dr[d];
				int newC = c+dc[d];
				int parId = getId(newR, newC);
				//root
				if(!water(newR, newC)) {
					par[0][id] = id;
					dep[id] = 0;
				}
				//found a cycle, parId is entry point of cycle
				else if(vis[parId] == 1) {
					cycleId = parId;
					par[0][id] = id;
					dep[id] = 0;
				}
				//has parent
				else {
					//if parent is in a cycle, insert into start of cycle
					parId = getEntryPoint(parId);
					par[0][id] = parId;
					con[parId].push_back(id);
					if(vis[parId] == 0)
						dfs(newR, newC);
					dep[id] = dep[parId]+1;
				}
			}
		}
		vis[id] = 2;
		cycle[id] = cycleId;
		//out of cycle
		if(cycleId == id)
			cycleId = -1;
	};

	
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			if(water(r, c) && vis[getId(r, c)] == 0) {
				cycleId = -1;
				dfs(r, c);
			}
		}
	}
	
	for(int bit = 1; bit < 20; bit++) {
		for(int id = 0; id < n*m; id++) {
			par[bit][id] = par[bit-1][par[bit-1][id]];
		}
	}
	
	//is a ancestor of b
	auto anc = [&](int a, int b) {
		if(dep[a] > dep[b])
			return false;
		for(int bit = 19; bit >= 0; bit--) {
			if(dep[b]-dep[a] >= (1<<bit))
				b = par[bit][b];
		}
		return a == b;
	};
	
	vector<int> score(n*m);
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			if(grid[r][c] == '#') {
				vector<int> places;
				for(int d = 0; d < 4; d++) {
					int newR = r+dr[d];
					int newC = c+dc[d];
					if(water(newR, newC)) {
						int id = getId(newR, newC);
						places.push_back(id);
					}
				}
				vector<bool> mark(sz(places), true);
				for(int i = 0; i < sz(places); i++) {
					for(int j = i+1; j < sz(places); j++) {
						if(anc(places[i], places[j]))
							mark[j] = false;
						if(anc(places[j], places[i]))
							mark[i] = false;
					}
				}
				for(int i = 0; i < sz(places); i++) {
					if(mark[i])
						score[places[i]]++;
				}
			}
		}
	}
	
	int best = 0;
	
	function<void(int, int)> check = [&](int curr, int s) {
		s += score[curr];
		best = max(best, s);
		for(int next : con[curr])
			check(next, s);
	};
	
	for(int id = 0; id < n*m; id++) {
		//dfs from all roots
		if(par[0][id] == id) {
			check(id, 0);
		}
	}
	
	cout << best << "\n";
	
}