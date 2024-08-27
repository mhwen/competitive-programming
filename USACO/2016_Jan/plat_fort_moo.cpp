#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("fortmoo.in");
	ofstream cout("fortmoo.out");
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for(int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	vector<vector<int>> left(n, vector<int>(m));
	vector<vector<int>> up(n, vector<int>(m));
	for(int r = 0; r < n; r++) {
		int prev = -1;
		for(int c = 0; c < m; c++) {
			if(grid[r][c] == 'X')
				prev = c;
			left[r][c] = c-prev;
		}
	}
	for(int c = 0; c < m; c++) {
		int prev = -1;
		for(int r = 0; r < n; r++) {
			if(grid[r][c] == 'X')
				prev = r;
			up[r][c] = r-prev;
		}
	}
	int ans = 0;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			vector<vector<int>> prev(m+1);
			for(int back = 1; back <= up[r][c]; back++) {
				prev[left[r-back+1][c]].push_back(back);
			}
			set<int> vals;
			for(int back = c+1; back > left[r][c]; back--) {
				for(int b : prev[back])
					vals.insert(b);
			}
			for(int back = left[r][c]; back > 0; back--) {
				for(int b : prev[back])
					vals.insert(b);
				auto it = vals.upper_bound(up[r][c-back+1]);
				if(it != vals.begin()) {
					it--;
					ans = max(ans, back*(*it));
				}
			}
		}
	}
	cout << ans << "\n";
}