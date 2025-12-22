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
	    vector<int> a(2*n);
	    vector<int> nodes(n);
	    for(int i = 0; i < sz(a); i++) {
	        cin >> a[i];
	        a[i]--;
	        nodes[a[i]] += i;
	    }
	    vector<vector<int>> con(2*n);
	    for(int i = 0; i < 2*n-1; i++) {
	        int u, v;
	        cin >> u >> v;
	        u--; v--;
	        con[u].push_back(v);
	        con[v].push_back(u);
	    }
	    
	    vector<int> pairedWith(2*n, -1);
	    auto dfs = [&](auto&& self, int curr, int prev) -> int {
	        int child = -1;
	        for(int next : con[curr]) {
	            if(next == prev)
	                continue;
	            int res = self(self, next, curr);
	            if(res != -1)
	                child = res;
	        };
	        if(child == -1)
	            return curr;
	        else {
	            pairedWith[curr] = child;
	            pairedWith[child] = curr;
	            return -1;
	        }
	    };
	    
	    dfs(dfs, 0, -1);
	    
	    vector<pair<int, int>> ans;
	    vector<bool> used(2*n);
	    
	    for(int i = 0; i < 2*n; i++) {
	        if(!used[i] && pairedWith[i] != -1) {
	            assert(!used[pairedWith[i]]);
	            if(a[i] == a[pairedWith[i]]) {
	                used[i] = used[pairedWith[i]] = true;
	                continue;
	            }
	            vector<int> left{pairedWith[i]}, right{i};
	            int curr = i;
	            bool cycleFound = false;
	            while(true) {
	                int next = nodes[a[curr]]-curr;
	                int nextPair = pairedWith[next];
	                //endpoint
	                if(nextPair == -1) {
	                    right.push_back(next);
	                    break;
	                }
	                //found cycle
	                else if(next == pairedWith[i] && nextPair == i) {
	                    cycleFound = true;
	                    break;
	                }
	                right.push_back(next);
	                right.push_back(nextPair);
	                curr = nextPair;
	            }
	            if(!cycleFound) {
	                curr = pairedWith[i];
	                while(true) {
                        int next = nodes[a[curr]]-curr;
                        int nextPair = pairedWith[next];
                        //endpoint
                        if(nextPair == -1) {
                            left.push_back(next);
                            break;
                        }
                        //found cycle
                        else if(next == pairedWith[i] && nextPair == i) {
                            //shouldn't happen
                            assert(false);
                        }
                        left.push_back(next);
	                    left.push_back(nextPair);
                        curr = nextPair;
                    }
	            }
	            
	            reverse(all(left));
	            left.insert(left.end(), all(right));
	            for(int l : left)
	                used[l] = true;
	            int L = 0, R = sz(left)-2;
	            while(L < R)
	                ans.emplace_back(left[L++], left[R--]);
	        }
	    }
	    cout << sz(ans) << "\n";
	    for(auto [u, v] : ans)
	        cout << u+1 << " " << v+1 << "\n";
	    
	}
}