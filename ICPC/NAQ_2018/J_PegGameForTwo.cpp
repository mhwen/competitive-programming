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

int dr[6] = {0, 0, -1, -1, 1, 1};
int dc[6] = {-1, 1, 0, -1, 0, 1};

bool bound(int r, int c) {
	if(r < 0 || r >= 5)
		return false;
	if(c < 0 || c > r)
		return false;
	return true;
}

map<vector<vector<int>>, int> seen;

int solve(vector<vector<int>>& board, int p) {
	if(seen.count(board))
		return seen[board];
	int best = p ? -INF : INF;
	bool ended = true;
	for(int r = 0; r < 5; r++) {
		for(int c = 0; c < sz(board[r]); c++) {
			for(int d = 0; d < 6; d++) {
				int ri = r+dr[d];
				int ci = c+dc[d];
				int re = r+dr[d]*2;
				int ce = c+dc[d]*2;
				if(bound(r, c) && bound(ri, ci) && bound(re, ce)) {
					if(board[r][c] && board[ri][ci] && !board[re][ce]) {
						ended = false;
						int hold = board[r][c];
						int gain = board[ri][ci];
						board[r][c] = 0;
						board[ri][ci] = 0;
						board[re][ce] = hold;
						if(p) 
							best = max(best, gain*hold+solve(board, 1-p));
						else 
							best = min(best, -gain*hold+solve(board, 1-p));
						board[r][c] = hold;
						board[ri][ci] = gain;
						board[re][ce] = 0;
					}
				}
			}
		}
	}
	if(ended)
		best = 0;
	seen[board] = best;
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<int>> board(5);
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j <= i; j++) {
			int v;
			cin >> v;
			board[i].push_back(v);
		}
	}
	cout << solve(board, 1) << "\n";
}