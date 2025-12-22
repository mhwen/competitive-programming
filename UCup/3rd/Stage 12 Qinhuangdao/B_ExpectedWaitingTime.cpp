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

int MOD;

struct mi {
	int v;
	mi() : mi(0) {}
	mi(int _v) : v(_v) {
		if (v >= MOD) v -= MOD;
		if (v < 0) v += MOD;
	}
	mi(ll _v) : mi((int)(_v % MOD)) {}
	mi operator+(const mi &m2) const { return mi(v - MOD + m2.v); }
	mi operator-(const mi &m2) const { return mi(v - m2.v); }
	mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
	mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
	mi &operator+=(const mi &m2) { return *this = *this + m2; }
	mi &operator-=(const mi &m2) { return *this = *this - m2; }
	mi &operator*=(const mi &m2) { return *this = *this * m2; }
	mi &operator/=(const mi &m2) { return *this = *this / m2; }
	mi pow(ll e) const {
		mi res = 1;
		mi n = *this;
		while (e > 0) {
			if (e & 1) res *= n;
			n *= n;
			e >>= 1;
		}
		return res;
	}
	mi inv() const {
		return pow(MOD - 2);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    ll b0, A, B;
	    cin >> n >> MOD >> b0 >> A >> B;
	    
	    vector<mi> fact(2*n+1);
	    fact[0] = mi(1);
	    for(int i = 1; i < sz(fact); i++)
	        fact[i] = fact[i-1]*i;
	    vector<mi> invFact(sz(fact));
	    invFact.back() = fact.back().inv();
	    for(int i = sz(invFact)-2; i >= 0; i--)
	        invFact[i] = invFact[i+1]*(i+1);
	    
	    auto catalan = [&](int N) {
	        return fact[2*N]*invFact[N+1]*invFact[N];
	    };
	    
	    vector<mi> b(2*n);
	    b[0] = b0*A+B;
	    for(int i = 1; i < sz(b); i++)
	    	b[i] = b[i-1]*A+B;
	    	
	    vector<mi> suf(2*n);
	    for(int i = 2*n-2; i >= 0; i--)
            suf[i] += suf[i+1]+b[i+1]+1;

	    vector<mi> triangle(n+1);
	    triangle[0] = 0;
	    for(int i = 1; i < sz(triangle); i++) {
	        triangle[i] = triangle[i-1]+catalan(n-i)*catalan(i-1);
	    }

	    mi ans(0);
	    for(int i = 2*n-1; i >= n; i--) {
	        ans += (triangle[(2*n-i)/2]-triangle[(i+1)/2])*(suf[i]-suf[2*n-1-i]);
	    }

	    cout << (ans*catalan(n).inv()).v << "\n";
	}
}