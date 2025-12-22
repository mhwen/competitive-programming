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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int q;
        cin >> q;
        int prev = -1;
        pair<int, int> curr{0, -1};
        vector<pair<int, int>> lens;
        for(int i = 0; i < q; i++) {
            int c;
            int x;
            cin >> c >> x;
            if(c == prev)
                curr.first++;
            else
                curr = {1, c};
            if(lens.empty() || curr.first > lens.back().first)
                lens.pb(curr);
            prev = c;
            
            auto it = lower_bound(all(lens), pair{x, 0});
            if(it != lens.end()) {
                auto [L, C] = *it;
                assert(L == x);
                if(C == 1)
                    cout << 1 << "\n";
                else
                    cout << 0 << "\n";
            }
            else {
                auto [L, C] = curr;
                mi tt = mi(2).pow(x-1).inv();
                mi v1 = tt * (mi(1)-(mi(1)-tt).pow(2)).inv();
                mi v0 = (mi(1)-tt)*v1;
                
                ll v = x-L;
                mi T = mi(2).pow(v).inv();
                if(C == 0)
                    cout << (mi(1)-T)*v1 << "\n";
                else 
                    cout << T + (mi(1)-T)*v0 << "\n";
            }
            
        }
    }
}