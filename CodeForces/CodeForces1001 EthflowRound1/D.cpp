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
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<ll> l(n);
	    vector<ll> r(n);
	    for(int i = 0; i < n; i++)
	        cin >> l[i] >> r[i];
	    vector<vector<int>> con(n);
	    for(int i = 0; i < n-1; i++) {
	        int a, b;
	        cin >> a >> b;
	        a--; b--;
	        con[a].push_back(b);
	        con[b].push_back(a);
	    }
	    vector<ll> val(n);
	    ll add = 0;
	    function<void(int, int)> dfs = [&](int curr, int prev) {
	        ll greatest = 0;
	        for(int next : con[curr]) {
	            if(next == prev)
	                continue;
	            dfs(next, curr);
	            greatest = max(greatest, val[next]);
	        }
	        ll L = l[curr];
	        ll R = r[curr];
	        if(greatest <= L) {
	            val[curr] = L;
	        }
	        else if(greatest <= R) {
	            val[curr] = greatest;
	        }
	        else {
	            ll additional = 0;
	            for(int next : con[curr]) {
	                if(next == prev)
	                    continue;
	                if(val[next] > R) {
	                    additional += val[next]-R;
	                }
	            }
	            val[curr] = R;
	            add += additional;
	        }
	        // cout << "at " << curr+1 << " val: " << val[curr] << " " << L << " lr " << R << " gr " << greatest << endl;
	    };
	    dfs(0, -1);
	    cout << val[0]+add << "\n";
	}
}