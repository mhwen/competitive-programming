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

constexpr ll MOD = 998244353;
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<mi> fact(2e5+5);
    vector<mi> invFact(sz(fact));
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i;
        invFact[i] = fact[i].inv();
    }
    auto choose = [&](ll a, ll b) {
        if(a < b)
            return mi(0);
        return fact[a]*invFact[b]*invFact[a-b];
    };
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if(accumulate(all(a), 0LL) != n) {
            cout << 0 << "\n";
            continue;
        }
        mi ways = 1;
        ll used = 0;
        ll open = n%2 ? -1 : -2;
        for(int i = n/2; i >= 0; i--) {
            open += 2;
            ll rem = open-used;
            ways = ways*choose(rem, a[i]);
            used += a[i];
        }
        if(used != n)
            ways = 0;
        cout << ways << "\n";
    }
}