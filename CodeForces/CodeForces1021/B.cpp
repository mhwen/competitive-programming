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

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, m, k;
	    cin >> n >> m >> k;
	    auto id = [&](int x, int y) {
	        return x*(m+1)+y;
	    };
	    k++;
	    vector<int> x(k);
	    vector<int> y(k);
	    map<int, vector<int>> con;
	    map<int, int> in;
	    for(int i = 0; i < k; i++)
	        cin >> x[i] >> y[i];
	    
	    bool bad = false;
	    for(int i = 0; i < k-1; i++) {
	        int dx = x[i+1]-x[i];
	        int dy = y[i+1]-y[i];
	        if(abs(dx)+abs(dy) != 2) {
	            bad = true;
	            break;
	        }
	        if(dx == 0 || dy == 0) {
	            int X = x[i]+dx/2;
	            int Y = y[i]+dy/2;
	            in[id(X, Y)]++;
	            if(in[id(X, Y)] > 1) {
	                bad = true;
	                break;
	            }
	        }
	        else {
	            int nx = x[i]+dx;
	            int ny = y[i]+dy;
	            con[id(nx, y[i])].pb(id(x[i], ny));
	            con[id(x[i], ny)].pb(id(nx, y[i]));
	        }
	    }
	    set<int> vis;
	    ll ans = 1;
	    
	    for(auto& [i, _con] : con) {
	        if(vis.count(i))
	            continue;
	        int cycles = 0;
	        int sz = 0;
	        int deg = 0;
	        
	        function<void(int, int)> dfs = [&](int curr, int prev) {
	            sz++;
	            deg += in[curr];
	            vis.insert(curr);
	            for(int next : con[curr]) {
	                if(next == prev)
	                    continue;
	                    
	                if(vis.count(next))
	                    cycles++;
	                else
	                    dfs(next, curr);
	            }
	        };
	        dfs(i, -1);
	        cycles/=2;
	        if(deg > 1 || cycles > 1) {
	            bad = true;
	            break;
	        }
	        else if(deg == 0) {
	            if(cycles)
	                ans = ans*2%MOD;
	            else
	                ans = ans*sz%MOD;
	        }
	        else {
	            if(cycles) {
	                bad = true;
	                break;
	            }
	        }
	    }
	    if(bad)
	        ans = 0;
	    
	    cout << ans << "\n";
	    
	}
}