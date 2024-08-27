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
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> pows(3000);
	pows[0] = 1;
	for(int i = 1; i < (int)pows.size(); i++) {
		pows[i] = pows[i-1]*2%MOD;
	}
	int n, m;
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m, -1));
	ll ways = 0;
	function<void(int)> count = [&](int pos) {
		int rem = n*m-1-pos;
		int r = pos/m;
		int c = pos%m;
		if(rem < 0)
			return;
		grid[r][c] = 0;
		bool continueZero = true;
		if(r > 0 && c > 0) {
			int ones = grid[r][c]+grid[r-1][c-1]+grid[r-1][c]+grid[r][c-1];
			if(ones%2==1) {
				ways = (ways+pows[rem])%MOD;
				continueZero = false;
			}
		}
		if(continueZero)
			count(pos+1);
		
		grid[r][c] = 1;
		bool continueOne = true;
		if(r > 0 && c > 0) {
			int ones = grid[r][c]+grid[r-1][c-1]+grid[r-1][c]+grid[r][c-1];
			if(ones%2==1) {
				ways = (ways+pows[rem])%MOD;
				continueOne = false;
			}
		}
		if(continueOne)
			count(pos+1);
		grid[r][c] = 0;
	};
	count(0);
	cout << ways << "\n";
}