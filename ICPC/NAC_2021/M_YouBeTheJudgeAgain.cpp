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
#define pb push_back

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector grid((1<<n), vector<int>(1<<n));
	map<int, vector<pair<int, int>>> freq;
	for(int r = 0; r < sz(grid); r++) {
	    for(int c = 0; c < sz(grid[0]); c++) {
	        cin >> grid[r][c];
	        freq[grid[r][c]].pb({r, c});
	    }
	}
	
	auto get = [&](int r, int c) {
	    if(r < 0 || c < 0 || r >= sz(grid) || c >= sz(grid[0]))
	        return -1;
	    return grid[r][c];
	};
	
	auto check = [&](int r, int c) {
	    for(int d = 0; d < 4; d++) {
	        int nd = (d+1)%4;
	        if(get(r+dr[d], c+dc[d]) == grid[r][c] && get(r+dr[nd], c+dc[nd]) == grid[r][c])
	            return true;
	    }
	    return false;
	};
	
	int ans = 1;
	for(auto [v, pos] : freq) {
	    int cnt = sz(pos);
	    if(v == 0) {
	        if(cnt != 1) {
	            ans = 0;
	            break;
	        }
	    }
	    else {
	        if(cnt != 3) {
	            ans = 0;
	            break;
	        }
	        bool found = false;
	        for(auto [r, c] : pos) {
	            if(check(r, c))
	                found = true;
	        }
	        if(!found) {
	            ans = 0;
	            break;
	        }
	    }
	}
	cout << ans << "\n";
}