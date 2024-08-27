#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> grid(n);
	for(int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	vector<string> mask(n);
	for(int i = 0; i < n; i++)
		cin >> mask[i];
	vector<vector<vector<int>>> vis(n, vector<vector<int>>(m, vector<int>(k, -1)));
	priority_queue<tuple<int, int, int, int>> q;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			if(grid[r][c] == 'C') {
				q.push({0, r, c, 0});
			}
		}
	}
	while(!q.empty()) {
		auto[weight, row, col, time] = q.top();
		q.pop();
		if(row < 0 || col < 0 || row >= n || col >= m)
			continue;
		if(vis[row][col][time] != -1 || grid[row][col] == '#')
			continue;
		weight = -weight;
		vis[row][col][time] = weight;
		int cost = 1;
		if(mask[row][(col+time)%k] == '1')
			cost = 3;
		if(grid[row][col] == 'R') {
			cout << weight << "\n";
			break;
		}
			
		if(row < n-1 && grid[row+1][col] != '#' && vis[row+1][col][(time+1)%k] == -1)
			q.push({-(weight+cost), row+1, col, (time+1)%k});
		if(row > 0 && grid[row-1][col] != '#' && vis[row-1][col][(time+1)%k] == -1)
			q.push({-(weight+cost), row-1, col, (time+1)%k});
		if(col < m-1 && grid[row][col+1] != '#' && vis[row][col+1][(time+1)%k] == -1)
			q.push({-(weight+cost), row, col+1, (time+1)%k});
		if(col > 0 && grid[row][col-1] != '#' && vis[row][col-1][(time+1)%k] == -1)
			q.push({-(weight+cost), row, col-1, (time+1)%k});
	}
}