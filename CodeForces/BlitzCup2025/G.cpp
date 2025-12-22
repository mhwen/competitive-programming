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

int n = 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> evens;
    vector<int> odds;
    auto gen = [&](auto&& self, int id, int mask, vector<int>& v) -> void {
        if(id >= 25) {
            v.push_back(mask);
            return;
        }
        self(self, id+2, mask, v);
        self(self, id+2, mask|(1<<id), v);  
    };
    gen(gen, 0, 0, evens);
    gen(gen, 1, 0, odds);
    
    int t;
	cin >> t;
	while(t-->0) {
	    vector<string> grid(n);
	    for(int i = 0; i < n; i++)
	        cin >> grid[i];
	               
	    auto black = [&](int r, int c) {
	        if(r-1 < 0 || c-1<0 || r+1 >= n || c+1>=n)
	            return false;
	        return grid[r][c] == 'B' && 
	               grid[r+1][c+1] == 'B' && 
	               grid[r-1][c+1] == 'B' && 
	               grid[r+1][c-1] == 'B' && 
	               grid[r-1][c-1] == 'B';
	    };
	    
	    auto solve = [&](int p, vector<int>& masks) {
	        int best = n*n;
	        for(auto mask : masks) {
	            int cnt = 0;
    	        for(int b = 0; b < 25; b++) {
    	            int dr = b/5;
    	            int dc = b%5;
    	            if(mask&(1<<b)) {
    	                grid[1+dr][1+dc]++;
    	                cnt++;
    	            }
    	        }
    	        bool good = true;
    	        for(int r = 0; r < n; r++) {
    	            for(int c = 0; c < n; c++) {
    	                if((r+c)%2!=p)
    	                    continue;
    	                if(black(r, c))
    	                    good = false;
    	            }
    	        }
    	        for(int r = 0; r < n; r++) {
    	            for(int c = 0; c < n; c++) {
    	                if(grid[r][c] != 'B' && grid[r][c] != 'W')
    	                    grid[r][c]--; 
    	            }
    	        }
    	        if(good)
	                best = min(best, cnt);
	        }
	        return best;
	    };
	    cout << solve(0, evens)+solve(1, odds) << "\n";
	}
}