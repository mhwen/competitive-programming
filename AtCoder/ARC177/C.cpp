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
#include <deque>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
constexpr int INF = 1e9;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
		cin >> grid[i];
	
	auto bfs = [&](pair<int, int> start, pair<int, int> end, char color) {
		deque<pair<pair<int, int>, int>> q;
		q.push_back({start, 0});
		vector<vector<int>> dist(n, vector<int>(n, INF));
		while(!q.empty()) {
			auto curr = q.front();
			q.pop_front();
			int r = curr.first.first;
			int c = curr.first.second;
			int d = curr.second;
			if(dist[r][c] != INF)
				continue;
			dist[r][c] = d;
			for(int dir = 0; dir < 4; dir++) {
				int newR = r+dx[dir];
				int newC = c+dy[dir];
				if(newR < 0 || newC < 0 || newR >= n || newC >= n)
					continue;
				if(dist[newR][newC] != INF)
					continue;
				if(grid[newR][newC] == color)
					q.push_front({{newR, newC}, d});
				else
					q.push_back({{newR, newC}, d+1});
			}
		}
		return dist[end.first][end.second];
	};
	
	int ans = bfs({0, 0}, {n-1, n-1}, 'R')+bfs({0, n-1}, {n-1, 0}, 'B');
	cout << ans << "\n";
}