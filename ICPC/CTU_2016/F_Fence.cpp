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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	while(cin >> n >> m) {
		vector<string> grid(n);
		for(int r = 0; r < n; r++)
			cin >> grid[r];
			
		auto inside = [&](int r, int c) {
			return r >= 0 && r < n && c >= 0 && c < m;
		};
		
		int minR = n, maxR = 0;
		int minC = m, maxC = 0;
		int startR = -1, startC = -1;
		queue<pair<pair<int, int>, int>> q;
		vector rdegree(n, vector<int>(m));
		vector cdegree(n, vector<int>(m));
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] == 'O') {
					minR = min(r, minR);
					minC = min(c, minC);
					maxR = max(r, maxR);
					maxC = max(c, maxC);
				}
				if(grid[r][c] == 'X') {
					startR = r;
					startC = c;
				}
				for(int d = 0; d < 4; d++) {
					int newR = r+dr[d];
					int newC = c+dc[d];
					if(inside(newR, newC)) {
						rdegree[newR][newC] += abs(dr[d]);
						cdegree[newR][newC] += abs(dc[d]);
					}
				}
			}
		}
		
		vector vis(n, vector<bool>(m));
		
		function<void(int, int)> dfs = [&](int r, int c) {
			if(vis[r][c] || grid[r][c] == 'O')
				return;
			vis[r][c] = true;
			for(int d = 0; d < 4; d++) {
				int newR = r+dr[d];
				int newC = c+dc[d];
				if(inside(newR, newC)) {
					rdegree[newR][newC] -= abs(dr[d]);
					cdegree[newR][newC] -= abs(dc[d]);
					if(grid[newR][newC] != 'O' && rdegree[newR][newC] <= 1 && cdegree[newR][newC] <= 1 && !vis[newR][newC])
						dfs(newR, newC);
				}
			}
		};
		
		dfs(0, 0);
		dfs(0, m-1);
		dfs(n-1, 0);
		dfs(n-1, m-1);
		
		int h = maxR-minR+1;
		int w = maxC-minC+1;
		int perim = 2*(h+w);
		if(startR < minR || startR > maxR || startC < minC || startC > maxC)
			cout << perim << "\n";
		else if((h == 1 && n == 1) || (w == 1 && m == 1)) {
			cout << -1 << "\n";
		}
		else {
			if(h == 1 || w == 1)
				perim += 2;
			int cost = -perim-1;
			q.push({{startR, startC}, 0});
			while(!q.empty()) {
				auto curr = q.front();
				q.pop();
				int r = curr.first.first;
				int c = curr.first.second;
				int dist = curr.second;
				if(!inside(r, c) || vis[r][c]) {
					cost = dist*2;
					break;
				}
				if(grid[r][c] == 'O')
					continue;
				grid[r][c] = 'O';
				for(int d = 0; d < 4; d++) {
					int newR = r+dr[d];
					int newC = c+dc[d];
					q.push({{newR, newC}, dist+1});
				}
			}
			cout << perim+cost << "\n";
		}
	}
}