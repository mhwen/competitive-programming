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

constexpr ll MOD = 1e9+7;

struct mi {
	ll val;
	mi() : mi(0) {}
	mi(ll v) : val(v) {
		val %= MOD;
		if(val < 0)
			val += MOD;
	}
	mi operator+(mi m2) const { return mi(val+m2.val); }
	mi operator-(mi m2) const { return mi(val-m2.val); }
	mi operator*(mi m2) const { return mi(val*m2.val); }
	mi operator/(mi m2) const { return mi(val*m2.inv().val); }
	mi operator+=(mi m2) { return *this = *this+m2; }
	mi operator-=(mi m2) { return *this = *this-m2; }
	mi operator*=(mi m2) { return *this = *this*m2; }
	mi operator/=(mi m2) { return *this = *this/m2; }
	mi pow(ll b) const {
		mi res = 1;
		mi p = *this;
		while(b > 0) {
			if(b & 1) res *= p;
			p *= p;
			b >>= 1;
		}
		return res;
	}
	mi inv() const {
		return pow(MOD-2);
	}
	friend ostream& operator<<(ostream& os, mi m) {
		return os << m.val;
	}
};

int main() {
    
    vector<mi> fact(5001);
    vector<mi> invFact(5001);
    fact[0] = mi(1);
    invFact[0] = mi(1); 
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*mi(i);
        invFact[i] = fact[i].inv();
    }
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    vector<int> nums;
	    vector<bool> fixed(n);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        if(a[i] != -1) {
	            nums.push_back(a[i]);
	            fixed[a[i]] = true;
	        }
	    }
	    sort(all(nums));
	    nums.push_back(n);
	    vector<int> below(n);
	    for(int i = 0; i < n; i++) {
	        if(i > 0)
	            below[i] += below[i-1];
	        if(!fixed[i])
	            below[i]++;
	    }
	    
	    int openSpaces = n-sz(nums)+1;
	    
	    auto choose = [&](int A, int B) {
            if(A < B)
                return mi(0);
            return fact[A]*invFact[A-B];
        };
	    
	    auto calc = [&](int gap, int v) {
	        return choose(gap, below[v])*choose(openSpaces-below[v], openSpaces-below[v]);
	    };
	    
	    vector<vector<mi>> ways(n+1, vector<mi>(n+1));
	    for(int gap = 0; gap <= n; gap++) {
	        for(int i = 1; i <= n; i++) {
	            ways[gap][i] += ways[gap][i-1];
	            ways[gap][i] += calc(gap, i-1);
	        }
	    }
	    
	    mi ans(0);
	    
	    for(int l = 0; l < n; l++) {
	        int gap = 0;
	        vector<bool> seen(n+1);
	        int at = 0;
	        for(int r = l; r < n; r++) {
	            if(a[r] == -1)
	                gap++;
	            else
	                seen[a[r]] = true;
	            while(seen[nums[at]])
	                at++;
	            ans += ways[gap][nums[at]];
	        }
	    }
	    
	    cout << ans << "\n";
	}
}