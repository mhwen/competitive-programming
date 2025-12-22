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
    vector<mi> fact(1e5);
    vector<mi> invFact(1e5);
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
        int n;
        cin >> n;
        vector<int> p(n);
        vector<vector<int>> con(n);
        for(int i = 1; i < n; i++) {
            cin >> p[i];
            p[i]--;
            con[p[i]].pb(i);
        }
        vector<int> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        
        vector<mi> ways(n);
        vector<int> moves(n);
        function<void(int)> solve = [&](int curr) {
            vector<int> nexts;
            function<void(int)> find = [&](int me) {
                if(a[me] == 0 && me != curr) {
                    nexts.pb(me);
                    solve(me);
                    return;
                }
                for(int next : con[me])
                    find(next);
            };
            find(curr);
            
            ways[curr] = 1;
            for(int next : nexts) {
                moves[curr] += moves[next];
                ways[curr] *= ways[next];
            }
            int K = moves[curr];
            for(int next : nexts) {
                ways[curr] *= choose(K, moves[next]);
                K -= moves[next];
            }
            
            function<void(int)> upd = [&](int me) {
                a[me]--;
                for(int next : con[me])
                    upd(next);
            };
            
            upd(curr);
            moves[curr]++;
            
            nexts.clear();
            find(curr);
            int M = 0;
            for(int next : nexts) {
                M += moves[next];
                moves[curr] += moves[next];
                ways[curr] *= ways[next];
            }
            K = M;
            for(int next : nexts) {
                ways[curr] *= choose(K, moves[next]);
                K -= moves[next];
            }
        };
        solve(0);
        cout << ways[0] << "\n";
    }
}