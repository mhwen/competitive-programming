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
    vector<mi> fact(100000), invFact(sz(fact));
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i;
        invFact[i] = fact[i].inv();
    }
    auto assign = [&](int spots, int guys) {
        if(spots < guys)
            return mi(0);
        return fact[spots]*invFact[spots-guys];
    };
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    map<int, pair<int, int>> pos;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            int a;
            cin >> a;
            pos[a] = {r, c};
        }
    }
    vector<int> mexes{1};
    
    int lr = pos[0].first;
    int hr = lr;
    int lc = pos[0].second;
    int hc = lc;
    for(int i = 1; i < n*m; i++) {
        auto [r, c] = pos[i];
        if(r < lr || r > hr || c < lc || c > hc)
            mexes.pb(i+1);
        else
            mexes.back()++;
        lr = min(r, lr);
        hr = max(r, hr);
        lc = min(c, lc);
        hc = max(c, hc);
    }
    
    vector dp(n+2, vector<mi>(m+2));
    dp[1][1] = 1;
    for(int i = 1; i < sz(mexes); i++) {
        vector newDp(n+2, vector<mi>(m+2));
        for(int r = 1; r <= n; r++) {
            for(int c = 1; c <= m; c++) {
                newDp[r+1][c+1] += dp[r][c]*4;
                newDp[r+1][c] += dp[r][c]*c*2;
                newDp[r+1][c+1] -= dp[r][c]*c*2;
                newDp[r][c+1] += dp[r][c]*r*2;
                newDp[r+1][c+1] -= dp[r][c]*r*2;
            }
        }
        for(int r = 1; r <= n; r++) {
            for(int c = 1; c <= m; c++) {
                newDp[r][c] += newDp[r-1][c]+newDp[r][c-1]-newDp[r-1][c-1];
            }
        }
        for(int r = 1; r <= n; r++) {
            for(int c = 1; c <= m; c++) {
                int spots = r*c - mexes[i-1]-1;
                int add = mexes[i]-mexes[i-1]-1;
                newDp[r][c] *= assign(spots, add);
            }
        }
        swap(dp, newDp);
    }
    cout << dp[n][m] << "\n";
}