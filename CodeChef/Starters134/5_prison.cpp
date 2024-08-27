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
int dy[4] = {-1, 1, 0, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		n+=2; m+=2;
		// cout << n << " nm " << m << endl;
		vector<vector<char>> grid(n, vector<char>(m));
		for(int r = 1; r < n-1; r++) {
			for(int c = 1; c < m-1; c++) {
				cin >> grid[r][c];
			}
		}
		vector<vector<int>> vis(n, vector<int>(m, INF));
		deque<pair<pair<int, int>, int>> q;
		for(int r = 0; r < n; r++) {
			q.push_back({{r, 0}, 0});
			q.push_back({{r, m-1}, 0});
		}
		for(int c = 0; c < m; c++) {
			q.push_back({{0, c}, 0});
			q.push_back({{n-1, c}, 0});
		}
		while(!q.empty()) {
			auto curr = q.front();
			q.pop_front();
			int r = curr.first.first;
			int c = curr.first.second;
			int dist = curr.second;
			// cout << r << " " << c << " " << dist << " " << vis[r][c] << endl;
			if(vis[r][c] != INF)
				continue;
			vis[r][c] = dist;
			for(int d = 0; d < 4; d++) {
				int newR = dx[d]+r;
				int newC = dy[d]+c;
				if(newR < 0 || newC < 0 || newR >= n || newC >= m)
					continue;
				if(vis[newR][newC] != INF)
					continue;
				// cout << "adding " << newR << " " << newC << endl;
				if(grid[newR][newC] == '1')
					q.push_back({{newR, newC}, dist+1});
				else
					q.push_front({{newR, newC}, dist});
			}
		}
		int ans = 0;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] == '0')
					ans = max(ans, vis[r][c]);
			}
		}
		cout << ans << "\n";
	}
}