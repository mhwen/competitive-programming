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
    vector<mi> fact(1e6);
    vector<mi> invFact(sz(fact));
    fact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i;
    }
    invFact.back() = fact.back().inv();
    for(int i = sz(invFact)-2; i >= 0; i--) {
        invFact[i] = invFact[i+1]*(i+1);
    }
    
    auto choose = [&](int a, int b) {
        if(b > a)
            return mi(0);
        return fact[a]*invFact[b]*invFact[a-b];
    };
    
    mi twoInv = mi(2).inv();
    vector<mi> twoPows(1e6), twoInvs(1e6);
    twoInvs[0] = twoPows[0] = 1;
    for(int i = 1; i < sz(twoInvs); i++) {
        twoInvs[i] = twoInvs[i-1]*twoInv;
        twoPows[i] = twoPows[i-1]*2;
    }
    
    auto compute = [&](int free) {
        mi res = 0;
        for(int toZero = 0; toZero <= free; toZero++) {
            mi ways = choose(free, toZero);
            int amt = free-toZero;
            if(amt%2==0) {
                res += ways*fact[amt]*invFact[amt/2]*twoInvs[amt/2]*twoPows[toZero];
            }
        }
        return res;
    };
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<int> a(n+1);
        vector<int> deg(n+1);
        bool bad = false;
        set<pair<int, int>> s;
        for(int i = 0; i < n+1; i++) {
            cin >> a[i];
            if(a[i] != -1) {
                s.insert({min(i, a[i]), max(i, a[i])});
            }
        }
        for(auto [x, y] : s) {
            if(x > n || y > n) {
                bad = true;
                break;
            }
            deg[y]++;
            if(x != y && x != 0)
                deg[x]++;
        }

        if(*max_element(all(deg)) > 1)
            bad = true;
        if(bad) {
            cout << 0 << "\n";
            continue;
        }
        int free = 0;
        for(int i = 1; i <= n; i++) {
            if(deg[i] == 0)
                free++;
        }
        
        mi ans = compute(free);
        
        //subtract out the n->0 case
        if(deg[n] == 0) {
            ans -= compute(free-1);
        }
        cout << ans << "\n";
    }
}