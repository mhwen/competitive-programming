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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

// ll best = 0;
// vector<int> bb;
// 
// ll check(vector<int>& a) {
    // map<int, vector<int>> seen;
    // for(int i = 0; i < sz(a); i++) {
        // seen[a[i]].push_back(i);
    // }
    // ll res = 0;
    // for(auto [val, pos] : seen) {
        // if(sz(pos) > 1) {
            // res += pos.back()-pos.front();
        // }
    // }
    // return res;
// }
// 
// void brute(vector<int>& a, vector<int> curr, int at) {
    // if(at == sz(a)) {
        // ll val = check(curr);
        // if(val > best) {N
            // best = val;
            // bb = curr;
        // }
        // return;
    // }
    // for(int i = 1; i <= a[at]; i++) {
        // auto next = curr;
        // next.push_back(i);
        // brute(a, next, at+1);
    // }
// }

template<class F>
int ternSearch(int a, int b, F f) {
	assert(a <= b);
	while (b - a >= 5) {
		int mid = (a + b) / 2;
		if (f(mid) < f(mid+1)) a = mid; // (A)
		else b = mid+1;
	}
	rep(i,a+1,b+1) if (f(a) < f(i)) a = i; // (B)
	return a;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    vector<vector<int>> cnts(n+1);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        cnts[a[i]].push_back(i);
	    }
	    if(n == 1) {
	        cout << 0 << "\n";
	        continue;
	    }
	    
	    auto solve = [&](int cap) {
	        ll ans = 0;
	        vector<bool> used(n+1);
	        priority_queue<int> hi;
	        priority_queue<int> lo;
    	    for(int i = n; i >= 1; i--) {
    	        for(auto v : cnts[i]) {
    	            hi.push(v);
    	            lo.push(-v);
    	        }
    	        if(i <= cap) {
    	            while(used[hi.top()])
    	                hi.pop();
    	            while(used[-lo.top()])
    	                lo.pop();
    	            assert(hi.top() != lo.top());
    	            ans += hi.top()+lo.top();
    	            used[hi.top()] = true;
    	            used[-lo.top()] = true;
    	            hi.pop();
    	            lo.pop();
    	        }
    	    }
    	    return ans;
	    };
	    
	    // best = 0;
	    // bb.clear();
	    // brute(a, vector<int>{}, 0);
	    sort(all(a));
	    int at = 0;
	    int id = 1;
	    while(at < sz(a)) {
	        while(at < sz(a) && a[at] < id)
	            at++;
	        if(at >= sz(a)-1)
	            break;
	        at += 2;
	        id++;
	    }
	    // cout << "solves: ";
	    // for(int i = 1; i <= id-1; i++)
	        // cout << solve(i) << " ";
	    // cout << endl;
	    int i = ternSearch(1, id-1, solve);
        ll ans = solve(i);
	    
	    cout << ans << "\n";
        // if(ans != best) {
            // cout << "FAIL " << best << endl;
            // for(auto v : bb)
                // cout << v << " ";
            // cout << endl;
            // return -1;
        // }
	}
}