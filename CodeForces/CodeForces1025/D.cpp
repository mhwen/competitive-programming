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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, m, l;
	    cin >> n >> m >> l;
	    vector<ll> oddA;
	    ll reach = 0;
	    for(int i = 0; i < l; i++) {
	        ll a;
	        cin >> a;
	        reach += a;
	        if(a%2==1)
	            oddA.pb(a);
	    }
	    sort(all(oddA));
	    
	    ll evenReach = reach;
	    ll oddReach = reach;
	    if(oddA.empty())
	        oddReach = 0;
	    else if(sz(oddA)%2==0)
	        oddReach -= oddA.front();
	    else
	        evenReach -= oddA.front();
	    
	    vector<vector<int>> con(n);
	    for(int i = 0; i < m; i++) {
	        int u, v;
	        cin >> u >> v;
	        u--;
	        v--;
	        con[u].pb(v);
	        con[v].pb(u);
	    }
	    vector<ll> even(n, INF);
	    vector<ll> odd(n, INF);
	    queue<pair<int, int>> q;
	    q.push({0, 0});
	    while(!q.empty()) {
	        auto [curr, dist] = q.front();
	        q.pop();
	        if(dist%2==0) {
	            if(even[curr] <= dist)
	                continue;
	            even[curr] = dist;
	            for(int next : con[curr]) {
	                q.push({next, dist+1});
	            }
	        }
	        else {
	            if(odd[curr] <= dist)
	                continue;
	            odd[curr] = dist;
	            for(int next : con[curr]) {
	                q.push({next, dist+1});
	            }
	        }
	    }
	    for(int i = 0; i < n; i++) {
	        if(even[i] <= evenReach || odd[i] <= oddReach)
	            cout << 1;
	        else
	            cout << 0;
	    }
	    cout << "\n";
	    
	}
}