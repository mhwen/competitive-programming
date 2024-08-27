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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<char>> grid(n+2, vector<char>(m+2, 'a'));
	vector<vector<int>> component(n+2, vector<int>(m+2, -1));
	int count = 0;
	int id = 0;
	function<void(int, int, int)> dfs = [&](int r, int c, char color) {
		if(grid[r][c] != color || component[r][c] == id)
			return;
		component[r][c] = id;
		for(int i = 0; i < 4; i++) {
			dfs(r+dx[i], c+dy[i], color);
		}
	};
	
	for(int i = 0; i < n*m; i++) {
		id++;
		int r, c;
		char color;
		cin >> r >> c >> color;
		set<int> prev;
		for(int j = 0; j < 4; j++) {
			if(grid[r+dx[j]][c+dy[j]] == color)
				prev.insert(component[r+dx[j]][c+dy[j]]);
		}
		grid[r][c] = color;
		if((int)prev.size() > 1)
			dfs(r, c, color);
		else if((int)prev.size() == 1)
			component[r][c] = *prev.begin();
		else 
			component[r][c] = id;

		count += 1-(int)prev.size();
		cout << count << "\n";
	}
}