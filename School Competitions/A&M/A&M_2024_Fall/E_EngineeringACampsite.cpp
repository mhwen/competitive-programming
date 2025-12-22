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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
		cin >> grid[i];
	vector<char> roles(k);
	for(int i = 0; i < k; i++)
		roles[i] = (char)('A'+i);
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			if(grid[r][c] == 't')
				grid[r][c] = roles[(r+c)%sz(roles)];
			cout << grid[r][c];
		}
		cout << "\n";
	}
	
}