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
	int n, m;
	cin >> n >> m;
	
	set<vector<int>> dp;
	set<vector<int>> next;
	set<vector<int>> seen;
	
	auto conv = [&](vector<int>& cnts) {
	    vector<int> curr;
	    for(int i = 2; i <= n; i++)
	        for(int amt = 0; amt < cnts[i]; amt++)
	            curr.pb(i);
	    return pair{curr, cnts[1]};
	};
	
	int best = 0;
	
	auto check = [&](vector<int>& cnts, int cap) {
	    cap = min(cap, n-cap);
	    auto [curr, ones] = conv(cnts);
	    set<pair<vector<int>, int>> s;
	    s.insert({vector<int>(n+1), 0});
	    for(auto v : curr) {
	        set<pair<vector<int>, int>> nextS;
	        for(auto [pre, k] : s) {
	            for(int b = 0; b <= v && k+b <= cap; b++) {
	                if(b) pre[b]++;
	                if(v-b) pre[v-b]++;
	                nextS.insert({pre, k+b});
	                if(b) pre[b]--;
	                if(v-b) pre[v-b]--;
	            }
	        }
	        swap(s, nextS);
	    }
	    
	    for(auto [nn, k] : s) {
	        if(cap-ones <= k && k <= cap) {
	            nn[1] += ones;
	            if(!seen.count(nn)) {
    	            next.insert(nn);
    	            best = max(best, nn[1]);
    	            seen.insert(nn);
    	        }
	        }
	    }
	};
    vector<int> start(n+1);
    start[n] = 1;
	dp.insert(start);
	seen.insert(start);
	for(int i = 0; i < m && best < n; i++) {
	    int k;
	    cin >> k;
	    next.clear();
	    for(auto v : dp) {
	        if(best == n)
	            break;
	        check(v, k);
	    }
	    swap(dp, next);
	}
	cout << best << "\n";
}