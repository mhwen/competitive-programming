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
constexpr ll p = 2e5+3;

struct Hash {
    vector<ll> a;
    vector<ll> pows, pre;
    Hash() {}
    Hash(vector<ll>& _a) : a(_a), pows(sz(a)+1), pre(sz(a)+1) {
        pows[0] = 1;
        for(int i = 0; i < sz(a); i++) {
            pows[i+1] = pows[i]*p%MOD;
            pre[i+1] = (pre[i]*p+a[i])%MOD;
        }
    }
    ll get(int l, int r) {
        return (pre[r+1]-pre[l]*pows[r-l+1]%MOD+MOD)%MOD;
    }
};

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
		mi pp = *this;
		while(b > 0) {
			if(b & 1) res *= pp;
			pp *= pp;
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
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<vector<ll>> a(n);
        vector<Hash> h(n);
        int mx = 0;
        for(int i = 0; i < n; i++) {
            int s;
            cin >> s;
            mx = max(mx, s);
            a[i].resize(s);
            for(int j = 0; j < s; j++)
                cin >> a[i][j];
            h[i] = Hash(a[i]);
        }
        if(mx > 1) {
            mi ans = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    ans += sz(a[i])+sz(a[j]);
                    for(int len = min(sz(a[i]), sz(a[j])); len > 0; len--) {
                        int aEnd = sz(a[i])-1;
                        if(h[i].get(aEnd-len+1, aEnd) == h[j].get(0, len-1)) {
                            ans -= len;
                            break;
                        }
                    }
                }
            }
            cout << ans*mi(n).pow(2).inv() << "\n";
        }
        else {
            map<ll, ll> cnts;
            for(int i = 0; i < n; i++) {
                cnts[a[i][0]]++;
            }
            mi res = 2LL*n*n;
            for(auto [v, amt] : cnts)
                res -= amt*amt;
            cout << res*mi(n).pow(2).inv() << "\n";
        }
    }
}