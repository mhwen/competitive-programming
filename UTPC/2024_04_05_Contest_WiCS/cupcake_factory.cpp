#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
char dirs[4] = {'<', '>', '^', 'v'};

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<string> grid(n);
		for(int i = 0; i < n; i++)
			cin >> grid[i];
		vector<vector<vector<int>>> dists(n, vector<vector<int>>(m, vector<int>(2, INF)));
		priority_queue<pair<pair<int, int>, pair<int, int>>> q;
		q.push({{0, 1}, {0, 0}});
		while(!q.empty()) {
			auto curr = q.top();
			q.pop();
			int dist = -curr.first.first;
			int on = curr.first.second;
			int r = curr.second.first;
			int c = curr.second.second;
			if(r < 0 || c < 0 || r >= n || c >= m)
				continue;
			if(dists[r][c][on] != INF || grid[r][c] == '#')
				continue;
			dists[r][c][on] = dist;
			if(grid[r][c] == '.') {
				for(int i = 0; i < 4; i++)
					q.push({{-(dist+2), on}, {r+dx[i], c+dy[i]}});
			}
			else if(grid[r][c] == '!') {
				for(int i = 0; i < 4; i++)
					q.push({{-(dist+2), on}, {r+dx[i], c+dy[i]}});
				q.push({{-dist, 1-on}, {r, c}});
			}
			else {
				if(on) {
					for(int i = 0; i < 4; i++) {
						if(grid[r][c] == dirs[i])
							q.push({{-(dist+1), on}, {r+dx[i], c+dy[i]}});
					}
				}
				else {
					for(int i = 0; i < 4; i++) {
						q.push({{-(dist+2), on}, {r+dx[i], c+dy[i]}});
					}
				}

			}
		}
		cout << min(dists[n-1][m-1][0], dists[n-1][m-1][1]) << "\n";
	}
}