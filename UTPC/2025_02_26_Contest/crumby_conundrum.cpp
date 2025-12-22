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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<string> grid(n);
	for(int r = 0; r < n; r++)
	    cin >> grid[r];
	queue<pair<int, pair<int, int>>> qu;
	for(int r = 0; r < n; r++) {
	    for(int c = 0; c < n; c++) {
	        if(grid[r][c] == 'E')
	            qu.push({1, {r, c}});
	    }
	}
	int INF = n*n+1;
	vector<vector<int>> d(n, vector<int>(n, INF));
	while(!qu.empty()) {
	    auto [dist, pos] = qu.front();
	    qu.pop();
	    auto [r, c] = pos;
	    if(r < 0 || c < 0 || r >= n || c >= n)
	        continue;
	    if(grid[r][c] == '#' || d[r][c] != INF)
	        continue;
	    d[r][c] = dist;
	    qu.push({dist+1, {r+1, c}});
	    qu.push({dist+1, {r-1, c}});
	    qu.push({dist+1, {r, c+1}});
	    qu.push({dist+1, {r, c-1}});
	}
	int tot = 0;
	vector<int> amt(n*n+2);
	for(int r = 0; r < n; r++) {
	    for(int c = 0; c < n; c++) {
	        if(grid[r][c] == '.') {
	            tot++;
	            amt[d[r][c]]++;
	        }
	    }
	}
	for(int i = 1; i < sz(amt); i++)
	    amt[i] += amt[i-1];
	cout << fixed << setprecision(20);
	while(q-->0) {
	    int b;
	    cin >> b;
	    cout << (double)amt[b]/tot << "\n";
	}
}