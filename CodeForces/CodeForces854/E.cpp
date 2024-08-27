#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void dfs(int r, int c, vector<vector<char>>& grid, vector<vector<int>>& vis, int label, int n, int m) {
	if(r < 0 || r >= n || c < 0 || c >= m)
		return;
	if(vis[r][c] == label)
		return;

	if(grid[r][c] == '.')
		return;
	vis[r][c] = label;
	dfs(r+1, c, grid, vis, label, n, m);
	dfs(r-1, c, grid, vis, label, n, m);
	dfs(r, c+1, grid, vis, label, n, m);
	dfs(r, c-1, grid, vis, label, n, m);
}

void fill(vector<vector<char>>& grid, int n, int m) {
	bool found = true;
	while(found) {
		found = false;
		for(int r = 0; r < n; r++) {
			int left = n+m;
			int right = 0;
			for(int c = 0; c < m; c++) {
				if(grid[r][m-c-1] == '#') {
					left = m-c-1;
				}
				if(grid[r][c] == '#') {
					right = c;
				}
			}
			// cout << "row " << r << " " << left << " " << right << endl;
			for(int c = left; c <= right; c++) {
				if(grid[r][c] == '.') {
					grid[r][c] = '#';
					found = true;
				}
			}
		}
		
		for(int c = 0; c < m; c++) {
			int left = n+m;
			int right = 0;
			for(int r = 0; r < n; r++) {
				if(grid[n-r-1][c] == '#') {
					left = n-r-1;
				}
				if(grid[r][c] == '#') {
					right = r;
				}
			}
			for(int r = left; r <= right; r++) {
				if(grid[r][c] == '.') {
					grid[r][c] = '#';
					found = true;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int inputs;
	cin >> inputs;
	while(inputs-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<char>> grid(n, vector<char>(m));
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				cin >> grid[r][c];
			}
		}
		fill(grid, n, m);
		
		// for(auto& g : grid) {
			// for(auto c : g) {
				// cout << c;
			// }
			// cout << "\n";
		// }
		// cout << "\n";
		
		vector<vector<int>> vis(n, vector<int>(m));
		for(auto& g : vis) {
			for(auto& c : g) {
				c = 0;
			}
		}
		
		int firstR = -1, firstC = -1;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] == '#') {
					firstR = r;
					firstC = c;
					dfs(r, c, grid, vis, 1, n, m);
					goto A;
				}
			}
		}
		A:
		int secondR = -1, secondC = -1;
		bool good = true;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] == '#' && vis[r][c] == 0) {
					good = false;
					secondR = r;
					secondC = c;
					dfs(r, c, grid, vis, 2, n, m);
				}
			}
		}
		
		int firstLabel = 1, secondLabel = 2;
		
		if(!good) {
			if(firstR > secondR) {
				swap(firstR, secondR);
				swap(firstC, secondC);
				swap(firstLabel, secondLabel);
			}
			int point1r = 0, point1c = 0;
			int point2r = n+m, point2c = n+m;
			if(firstC < secondC) {
				for(int r = 0; r < n; r++) {
					for(int c = 0; c < m; c++) {
						if(vis[r][c] == firstLabel) {
							point1r = max(point1r, r);
							point1c = max(point1c, c);
						}
						if(vis[r][c] == secondLabel) {
							point2r = min(point2r, r);
							point2c = min(point2c, c);
						}
					}
				}
				grid[point1r][point1c] = '#';
				grid[point2r][point2c] = '#';

			}
			else {
				point1r = 0, point1c = n+m;
				point2r = n+m, point2c = 0;
				for(int r = 0; r < n; r++) {
					for(int c = 0; c < m; c++) {
						if(vis[r][c] == firstLabel) {
							point1r = max(point1r, r);
							point1c = min(point1c, c);
						}
						if(vis[r][c] == secondLabel) {
							point2r = min(point2r, r);
							point2c = max(point2c, c);
						}
					}
				}
				grid[point1r][point1c] = '#';
				grid[point2r][point2c] = '#';
			}
			fill(grid, n, m);
			
			int currR = point1r;
			int currC = point1c;
			while(currR < point2r) {
				grid[currR][currC] = '#';
				currR++;
			}
			while(currR > point2r) {
				grid[currR][currC] = '#';
				currR--;
			}
			
			while(currC < point2c) {
				grid[currR][currC] = '#';
				currC++;
			}
			while(currC > point2c) {
				grid[currR][currC] = '#';
				currC--;
			}
		}
		

		
		for(auto& g : grid) {
			for(auto c : g) {
				cout << c;
			}
			cout << "\n";
		}
		cout << "\n";
// 		
		// for(auto& g : vis) {
			// for(auto c : g) {
				// cout << c;
			// }
			// cout << "\n";
		// }
		
	}
	
}