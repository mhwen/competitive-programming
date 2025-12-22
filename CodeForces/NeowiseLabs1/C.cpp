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

constexpr ll INF = 1e18;

ll solve(vector<bool>& same, vector<bool>& down, vector<bool>& up, vector<ll>& a) {
    int n = sz(a);
    ll zero = 0;
    ll one = a[0];
    for(int i = 1; i < n; i++) {
        ll nextz = INF;
        ll nexto = INF;
        //00 or 11
        if(same[i-1]) {
            nextz = min(nextz, zero);
            nexto = min(nexto, one+a[i]);
        }
        //01
        if(up[i-1])
            nexto = min(nexto, zero+a[i]);
        //10
        if(down[i-1])
            nextz = min(nextz, one);
        zero = nextz;
        one = nexto;
    }
    return min(zero, one);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector h(n, vector<ll>(n));
	    for(int r = 0; r < n; r++) {
	        for(int c = 0; c < n; c++)
	            cin >> h[r][c];
	    }
	    vector<ll> a(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i];
        vector<ll> b(n);
	    for(int i = 0; i < n; i++)
	        cin >> b[i];
	    //0 0  -> no two same
	    //0 1  -> no one up
	    //1 0  -> no one down
	    //1 1  -> no two same
	    vector<bool> rs(n-1, true);
	    vector<bool> rd(n-1, true);
	    vector<bool> ru(n-1, true);
	    for(int r = 0; r < n-1; r++) {
	        for(int c = 0; c < n; c++) {
	            if(h[r][c] == h[r+1][c])
	                rs[r] = false;
	            if(h[r][c]+1 == h[r+1][c])
	                rd[r] = false;
	            if(h[r][c]-1 == h[r+1][c])
	                ru[r] = false;
	        }
	    }
	    vector<bool> cs(n-1, true);
	    vector<bool> cd(n-1, true);
	    vector<bool> cu(n-1, true);
	    for(int c = 0; c < n-1; c++) {
	        for(int r = 0; r < n; r++) {
	            if(h[r][c] == h[r][c+1])
	                cs[c] = false;
	            if(h[r][c]+1 == h[r][c+1])
	                cd[c] = false;
	            if(h[r][c]-1 == h[r][c+1])
	                cu[c] = false;
	        }
	    }
	    ll row = solve(rs, rd, ru, a);
	    ll col = solve(cs, cd, cu, b);
	    if(row == INF || col == INF)
	        cout << -1 << "\n";
	    else
	        cout << row+col << "\n";
	}
}