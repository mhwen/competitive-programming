#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int dx[] = {1, -1, 1, -1};
int dy[] = {0, 0, 1, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> grid(n, vector<int>(m));
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			cin >> grid[r][c];
		}
	}
	
	vector<vector<int>> covered(n, vector<int>(m));
	vector<vector<bool>> vis(n, vector<bool>(m));
	
	while(q-->0) {
		int startR, startC;
		cin >> startR >> startC;
		startR--; startC--;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				vis[r][c] = false;
			}
		}
		queue<pair<int, int>> myQ;
		myQ.push({startR, startC});
		while(!myQ.empty()) {
			auto curr = myQ.front();
			myQ.pop();
			int r = curr.first;
			int c = curr.second;
			if(vis[r][c])
				continue;
			vis[r][c] = true;
			covered[r][c]++;
			for(int i = 0; i < 4; i++) {
				int newR = r+dx[i];
				int newC = c+dy[i];
				if(newR < 0 || newC < 0 || newR >= n || newC >= m)
					continue;
				if(vis[newR][newC] || grid[newR][newC] > grid[r][c])
					continue;
				myQ.push({newR, newC});
			}
		}
	}
	
	int best = 0, R = 0, C = 0;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(covered[r][c] > best) {
				best = covered[r][c];
				R = r, C = c;
			}
		}
	}
	cout << R+1 << " " << C+1 << " " << best << "\n";
	
}