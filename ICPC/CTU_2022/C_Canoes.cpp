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

char dir[4] = {'L', 'R', 'U', 'D'};
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int h, w, n;
	cin >> h >> w >> n;
	vector grid(h, vector<bool>(w));
	vector endPoints(h, vector<vector<int>>(w));
	vector<pair<int, int>> start(n);
	vector<pair<int, int>> end(n);
	for(int i = 0; i < n; i++) {
		int x, y, k;
		char D;
		cin >> x >> y >> k >> D;
		x--; y--;
		start[i] = {x, y};
		for(int d = 0; d < 4; d++) {
			if(dir[d] == D) {
				int currX = x;
				int currY = y;
				for(int j = 0; j < k-2; j++) {
					currX += dx[d];
					currY += dy[d];
					if(grid[currX][currY]) {
						cout << "No\n";
						return 0;
					}
					grid[currX][currY] = true;
				}
				currX += dx[d];
				currY += dy[d];
				end[i] = {currX, currY};
			}
		}
		endPoints[start[i].first][start[i].second].push_back(i);
		endPoints[end[i].first][end[i].second].push_back(i);
	}
	
	vector<bool> vis(n);
	set<pair<int, int>> open;
	
	function<int(int)> dfs = [&](int curr) {
		int startX = start[curr].first;
		int startY = start[curr].second;
		int endX = end[curr].first;
		int endY = end[curr].second;
		if(!grid[startX][startY])
			open.insert(start[curr]);
		if(!grid[endX][endY])
			open.insert(end[curr]);
		vis[curr] = true;
		int cnt = 1;
		for(int next : endPoints[startX][startY])
			if(!vis[next])
				cnt += dfs(next);
		for(int next : endPoints[endX][endY])
			if(!vis[next])
				cnt += dfs(next);
		return cnt;
	};
	
	for(int i = 0; i < n; i++) {
		if(!vis[i]) {
			open.clear();
			int comp = dfs(i);
			if(comp > sz(open)) {
				cout << "No\n";
				return 0;
			}
		}
	}
	cout << "Yes\n";
}