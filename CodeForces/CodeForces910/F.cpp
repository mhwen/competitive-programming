#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int dirX[] = {1, -1, 0, 0};
int dirY[] = {0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<string> grid(n);
		for(int i = 0; i < n; i++) {
			cin >> grid[i];
		}
		int open = 0;
		vector<vector<int>> vis(n, vector<int>(m, -1));
		queue<pair<pair<int, int>, int>> q;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] == 'V')
					q.push({{r, c}, 0});
				if(grid[r][c] == '.')
					open++;
			}
		}
		while(!q.empty()) {
			auto curr = q.front();
			q.pop();
			int r = curr.first.first;
			int c = curr.first.second;
			int dist = curr.second;
			if(vis[r][c] != -1)
				continue;
			vis[r][c] = dist;
			for(int d = 0; d < 4; d++) {
				int newR = r+dirX[d];
				int newC = c+dirY[d];
				if(newR < 0 || newC < 0 || newR >= n || newC >= m)
					continue;
				if(vis[newR][newC] != -1 || grid[newR][newC] == '#')
					continue;
				q.push({{newR, newC}, dist+1});
			}
		}
		int count = 0;
		int shortest = n*m*2;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if((r == 0 || c == 0 || r == n-1 || c == m-1) && vis[r][c] != -1) {
					count++;
					shortest = min(shortest, vis[r][c]);
				}
			}
		}
		if(count == 0) {
			cout << open << "\n";
		}
		else if(count == 1) {
			cout << open-shortest << "\n";
		}
		else {
			vector<vector<vector<pair<int, int>>>> bestTwo(n, vector<vector<pair<int, int>>>(m));
			queue<pair<pair<int, int>, pair<int, int>>> myQ;
			for(int r = 0; r < n; r++) {
				for(int c = 0; c < m; c++) {
					if((r == 0 || c == 0 || r == n-1 || c == m-1) && vis[r][c] != -1) {
						myQ.push({{r, c}, {r*10000+c, 0}});
					}
				}
			}
			while(!myQ.empty()) {
				auto curr = myQ.front();
				myQ.pop();
				int r = curr.first.first;
				int c = curr.first.second;
				int from = curr.second.first;
				int dist = curr.second.second;
				// cout << r << " " << c << " " << from << " " << dist << endl;
				if((int)bestTwo[r][c].size() >= 2)
					continue;
				if((int)bestTwo[r][c].size() == 1 && bestTwo[r][c][0].first == from)
					continue;
				bestTwo[r][c].push_back({from, dist});
				for(int d = 0; d < 4; d++) {
					int newR = r+dirX[d];
					int newC = c+dirY[d];
					if(newR < 0 || newC < 0 || newR >= n || newC >= m)
						continue;
					if((int)bestTwo[newR][newC].size() >= 2 || grid[newR][newC] == '#')
						continue;
					myQ.push({{newR, newC}, {from, dist+1}});
				}
			}
			int best = n*m*2;
			for(int r = 0; r < n; r++) {
				for(int c = 0; c < m; c++) {
					if(vis[r][c] != -1 && (int)bestTwo[r][c].size() == 2) {
						best = min(best, vis[r][c]+bestTwo[r][c][0].second+bestTwo[r][c][1].second);
					}
				}
			}
			// cout << "best " << best << endl;
			cout << open-best << "\n";
		}
	}
}