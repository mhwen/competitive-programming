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

//12:32
//12:42

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	map<string, pair<int, int>> games;
	
	vector<vector<char>> grid(3, vector<char>(3, '.'));
	
	auto wins = [&]() {
		for(int r = 0; r < 3; r++) {
			if(grid[r][0] != '.' && grid[r][0] == grid[r][1] && grid[r][1] == grid[r][2])
				return grid[r][0];
		}
		for(int c = 0; c < 3; c++) {
			if(grid[0][c] != '.' && grid[0][c] == grid[1][c] && grid[1][c] == grid[2][c])
				return grid[0][c];
		}
		if(grid[0][0] != '.' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
			return grid[0][0];
		if(grid[0][2] != '.' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
			return grid[0][2];
		return '.';
	};
	
	auto convert = [&]() {
		string s;
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) 
				s += grid[r][c];
		}
		return s;
	};
	
	function<void(char)> search = [&](char ch) {
		
		char winner = wins();
		if(winner == 'X') {
			games[convert()] = {1, 0};
			return;
		}
		else if(winner == 'O') {
			games[convert()] = {0, 1};
			return;
		}
		
		char nextCh = (ch == 'X') ? 'O' : 'X';
		pair<int, int> record;
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < 3; c++) {
				if(grid[r][c] == '.') {
					grid[r][c] = ch;
					search(nextCh);
					record.first += games[convert()].first;
					record.second += games[convert()].second;
					grid[r][c] = '.';
				}
			}
		}
		games[convert()] = record;
	};
	
	search('X');
	
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if(games.count(s))
			cout << games[s].first << " " << games[s].second << "\n";
		else
			cout << "-1 -1\n";
	}
}