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
	    int n, m;
	    cin >> n >> m;
	    vector<vector<int>> s(n);
	    for(int i = 0; i < n; i++) {
	        int k;
	        cin >> k;
	        for(int j = 0; j < k; j++) {
	            int e;
	            cin >> e;
	            s[i].push_back(e);
	        }
	        sort(all(s[i]));
	    }
	    vector<vector<int>> e(n);
	    vector<int> kill(n+1);
	    for(int i = 0; i < m; i++) {
	        int l, r;
	        cin >> l >> r;
	        l--;
	        e[l].push_back(r);
	        kill[r]++;
	    }
	    multiset<int> used;
	    multiset<int> available;
	    string ans = "YES";
	    for(int i = 0; i < n; i++) {
	        for(int l = 0; l < kill[i]; l++) {
	            if(available.find(i) != available.end())
	                available.erase(available.find(i));
	            else {
    	            assert(used.find(i) != used.end());
	                used.erase(used.find(i));
	            }
	        }
		    for(auto r : e[i])
	            available.insert(r);
	        int rem = sz(available);
	        if(rem < sz(s[i])) {
	            ans = "NO";
	            goto done;
	        }
	        for(int j = 0; j < sz(s[i]); j++) {
	            if(s[i][j] <= j) {
	                ans = "NO";
	                goto done;
	            }
	            auto it = *available.rbegin();
	            used.insert(it);
	            available.erase(available.find(it));
	        }
	    }
	    done:
	    cout << ans << "\n";
	}
}