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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<int> mobius(1e6+1);
    mobius[1] = -1;
    for (int i = 1; i < sz(mobius); i++) {
    	if (mobius[i]) {
    		mobius[i] = -mobius[i];
    		for (int j = 2 * i; j < sz(mobius); j += i) {
    		    mobius[j] += mobius[i];
    		}
    	}
    }
    vector<vector<int>> factors(1e6+1);
	for(int i = 2; i < sz(factors); i++) {
	    for(int j = i; j < sz(factors); j+=i)
	        factors[j].pb(i);
	}
	
	int t;
	cin >> t;
	while(t-->0) {
	    int n, m;
	    cin >> n >> m;
	    vector<int> a(n);

	    auto getCoprimes = [&](int id) {
            vector<int> res;
            for(int i = 0; i < n; i++) {
                if(i == id)
                    continue;
                if(gcd(a[i], a[id]) == 1)
                    res.pb(i);
            }	        
            return res;
	    };
	    
	    vector<int> cnts(m+1);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        for(auto f : factors[a[i]])
	            cnts[f]++;
	    }
	    vector<pair<int, int>> candidates;
	    for(int i = 0; i < n; i++) {
	        int coprime = n;
	        for(auto f : factors[a[i]]) {
	            coprime += mobius[f]*cnts[f];
	        }
	        if(a[i] == 1)
	            coprime--;
	        if(coprime)
	            candidates.pb({coprime, i});
	    }
	    if(sz(candidates) < 4) {
	        cout << 0 << "\n";
	        continue;
	    }
	    sort(all(candidates));
	    reverse(all(candidates));
	    int C1 = candidates[0].second;
	    vector<int> adj1 = getCoprimes(C1);
	    
	    vector<int> ans(4);
	    // star
	    if(sz(adj1) == sz(candidates)-1) {
	        int C2 = candidates[1].second;
	        vector<int> adj2 = getCoprimes(C2);
	        if(sz(adj2) == 1) {
	            cout << 0 << "\n";
	            continue;
	        }
	        ans[0] = C2;
	        if(adj2[0] == C1)
	            ans[1] = adj2[1];
	        else
	            ans[1] = adj2[0];
	    }
	    else {
	        vector<bool> ignore(n);
	        for(int adj : adj1)
	            ignore[adj] = true;
	        ignore[C1] = true;
	        int C2 = -1;
	        for(auto [cnt, i] : candidates) {
	            if(!ignore[i])
	                C2 = i;
	        }
	        assert(C2 != -1);
	        vector<int> adj2 = getCoprimes(C2);
	        ans[0] = C2;
	        ans[1] = adj2.front();
	    }
	    ans[2] = C1;
        for(int next : adj1)
            if(next != ans[0] && next != ans[1])
                ans[3] = next;
        assert(gcd(a[ans[0]], a[ans[1]]) == 1);
        assert(gcd(a[ans[2]], a[ans[3]]) == 1);
        for(int v : ans)
            cout << v+1 << " ";
        cout << "\n";
	}
}