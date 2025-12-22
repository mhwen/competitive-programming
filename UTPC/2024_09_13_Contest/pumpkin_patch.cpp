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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for(int r = 0; r < n; r++)
		cin >> grid[r];
	vector<vector<int>> corn(n, vector<int>(m, -1));
	int id = 0;
	queue<pair<pair<pair<int, int>, int>, pair<int, int>>> q;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			if(grid[r][c] == 'C')
				corn[r][c] = id++;
			if(grid[r][c] == 'S')
				q.push({{{r, c}, 0}, {0, 0}});
		}
	}
	
	auto take = [&](int r, int c, int& mask) {
		int cid = corn[r][c];
		if(mask&(1<<cid))
			return false;
		mask |= (1<<cid);
		return true;
	};
	
	vector vis = vector(n, vector(m, vector(1<<id, vector<int>(id+1, INF))));
	int ans = -1;
	while(!q.empty()) {
		auto curr = q.front();
		q.pop();
		int r = curr.first.first.first;
		int c = curr.first.first.second;
		int dist = curr.first.second;
		int mask = curr.second.first;
		int cornLeft = curr.second.second;
		if(r < 0 || c < 0 || r >= n || c >= m)
			continue;
		if(grid[r][c] == 'P')
			continue;
		if(grid[r][c] == 'J') {
			if(cornLeft == 0)
				continue;
			else
				cornLeft--;
		}
		if(grid[r][c] == 'C' && take(r, c, mask))
			cornLeft++;
		if(vis[r][c][mask][cornLeft] != INF)
			continue;
		vis[r][c][mask][cornLeft] = dist;
		if(grid[r][c] == 'E') {
			ans = dist;
			break;
		}
		for(int d = 0; d < 4; d++) {
			int newR = r+dx[d];
			int newC = c+dy[d];
			q.push({{{newR, newC}, dist+1}, {mask, cornLeft}});
		}
	}
	if(ans != -1)
		cout << ans << "\n";
	else
		cout << "SPOOKED!\n";
}