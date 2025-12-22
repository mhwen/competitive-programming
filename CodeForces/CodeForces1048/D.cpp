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
    vector<mi> fact (5001);
    vector<mi> invFact(sz(fact));
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i;
        invFact[i] = fact[i].inv();
    }
    auto choose = [&](int a, int b) {
        if(a < b)
            return mi(0);
        return fact[a]*invFact[b]*invFact[a-b];
    };
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        ll m;
        int n, q;
        cin >> n >> m >> q;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        vector<pair<int, ll>> queries(q);
        for(int i = 0; i < q; i++) {
            int p;
            ll x;
            cin >> p >> x;
            p--;
            queries[i] = {p, x};
        }
        sort(all(queries), [](auto A, auto B) {
            return A.second-A.first < B.second-B.first; 
        });
        for(int i = 0; i < n; i++) {
            mi ans(0);
            vector<ll> lefts, rights, selfs;
            for(auto [id, pos] : queries) {
                ll me = pos+i-id;
                if(id > i)
                    rights.pb(me);
                else if(id < i)
                    lefts.pb(me);
                else
                    selfs.pb(me);
            }
            mi stay = fact[q];
            for(auto v : selfs) {
                //before = rights <= v
                //         lefts  >= v
                //         other selfs
                int before = sz(selfs)-1;
                before += (int)(lefts.end()-lower_bound(all(lefts), v));
                before += (int)(upper_bound(all(rights), v)-rights.begin());
                int noop = q-before-1;
                mi ways = choose(q, noop)*fact[noop];
                ways *= fact[before];
                ans += ways*v;
                stay -= ways;
            }
            for(auto v : lefts) {
                //before = rights <= v        LE
                //         selfs  <= v
                //         lefts  >  v        G
                //         selfs  >  v  
                //         lefts  == v        E
                
                //noops =  rights >  v
                //         lefts  <  v
                
                // all G must occur before last LE
                int LE = (int)(upper_bound(all(rights), v)-rights.begin());
                LE += (int)(upper_bound(all(selfs), v)-selfs.begin());
                int G = (int)(lefts.end()-upper_bound(all(lefts), v));
                G += (int)(selfs.end()-upper_bound(all(selfs), v));
                int E = (int)(upper_bound(all(lefts), v)-lower_bound(all(lefts), v))-1;
                int noops = q-1-LE-G-E;
                mi ways = choose(q, noops)*fact[noops];
                int rem = q-noops-1;
                ways *= choose(rem, E)*fact[E];
                rem -= E;
                assert(rem == LE+G);
                if(G) {
                    ways *= fact[rem-1]*LE;
                }
                else {
                    ways *= fact[rem];
                    if(v < a[i] && rem == 0)
                        ways = 0;
                }
                
                // cout << i+1 << ": " << ways << " " << v << endl;
                ans += ways*v;
                stay -= ways;
            }
            
            for(auto v : rights) {
                //before = lefts  >= v        GE
                //         selfs  >= v
                //         rights <  v        L
                //         selfs  <  v  
                //         rights == v        E
                
                //noops =  lefts  <  v
                //       + rights >  v
                
                // all L must occur before last GE
                int GE = (int)(lefts.end()-lower_bound(all(lefts), v));
                GE += (int)(selfs.end()-lower_bound(all(selfs), v));
                int L = (int)(lower_bound(all(rights), v)-rights.begin());
                L += (int)(lower_bound(all(selfs), v)-selfs.begin());
                int E = (int)(upper_bound(all(rights), v)-lower_bound(all(rights), v))-1;
                int noops = q-1-GE-L-E;
                mi ways = choose(q, noops)*fact[noops];
                int rem = q-noops-1;
                ways *= choose(rem, E)*fact[E];
                rem -= E;
                assert(rem == GE+L);
                if(L) {
                    ways *= fact[rem-1]*GE;
                }
                else {
                    ways *= fact[rem];
                    if(v > a[i] && rem == 0)
                        ways = 0;
                }
                
                // cout << i+1 << ": " << ways << " " << v << endl;
                ans += ways*v;
                stay -= ways;
            }
            ans += stay*a[i];
            cout << ans << " ";
        }
        cout << "\n";
    }
}