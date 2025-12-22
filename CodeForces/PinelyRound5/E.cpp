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

ll brute(int n, int k, string s) {
    ll ans = 0;
    auto check = [&]() {
        int r = 0;
        bool bad = false;
        int z = 0, o = 0;
        for(int i = 0; i+k-1 < n; i++) {
            while(r-i < k) {
                if(s[r] == '0')
                    z++;
                else
                    o++;
                r++;
            }
            if(s[i] == '0' && z < o) {
                bad = true;
                break;
            }
            if(s[i] == '1' && o < z) {
                bad = true;
                break;
            }
            if(s[i] == '0')
                z--;
            else
                o--;
        }  
        if(!bad)
            ans++;
    };
    
    function<void(int)> dfs = [&](int curr) {
        if(curr == n) {
            check();
            return;
        }  
        if(s[curr] == '?') {
            s[curr] = '0';
            dfs(curr+1);
            s[curr] = '1';
            dfs(curr+1);
            s[curr] = '?';
        }
        else
            dfs(curr+1);
    };
    dfs(0);
    
    return ans;
}

int main() {
    vector<mi> fact(1e5+5);
    vector<mi> invFact(1e5+5);
    fact[0] = 1;
    for(int i = 1; i < sz(fact); i++)
        fact[i] = fact[i-1]*i;
    invFact.back()= fact.back().inv();
    for(int i = sz(invFact)-2; i >= 0; i--)
        invFact[i] = invFact[i+1]*(i+1);
    auto choose = [&](int a, int b) {
        // cout << "choosing " << a << " " << b << endl;
        if(a < b)
            return mi(0);
        return fact[a]*invFact[b]*invFact[a-b];
    };
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        
        auto solve = [&]() {
            mi ways = 0;
            vector<int> same(k-1), diff(k-1);
            for(int i = 1; i < n; i++) {
                if(s[i] == '?')
                    continue;
                if(s[i] == s[0])
                    same[i%(k-1)]++;
                else
                    diff[i%(k-1)]++;
            }
            int bads = 0;
            int sames = 0;
            int diffs = 0;
            int frees = 0;
            for(int i = 0; i < k-1; i++) {
                if(same[i] > 0 && diff[i] > 0)
                    bads++;
                else if(same[i] > 0)
                    sames++;
                else if(diff[i] > 0)
                    diffs++;
                else
                    frees++;
            }
            
            // cout << "FL: " << frees << endl;
        
            auto makeDiff = [&]() {
                // cout << sames << " " << bads << " " << frees << endl;
                if(bads == 0) {
                    int need = k/2-sames;
                    if(need >= 0 && need <= frees) {
                        // cout << "made diff " << choose(frees, need) << endl;
                        ways += choose(frees, need);
                    }
                }
            };
            
            bool stop = false;
            for(int i = 0; i+k < n; i++) {
                int next = i+1;
                // cout << "at " << next << endl;
                if(s[next] == '?') {
                    if(same[next%(k-1)] == 0) {
                        if(diff[next%(k-1)] == 0)
                            frees--;
                        // cout << "going " << endl;
                        makeDiff();
                        if(diff[next%(k-1)] == 0)
                            frees++;
                    }
                }
                else if(s[next] == s[0]) {
                    same[next%(k-1)]--;
                    if(same[next%(k-1)] == 0 && diff[next%(k-1)] > 0)
                        bads--;
                    if(same[next%(k-1)] == 0 && diff[next%(k-1)] == 0) {
                        sames--;
                        frees++;
                    }
                    continue;
                }
                else {
                    if(same[next%(k-1)] == 0)
                        makeDiff();
                    stop = true;
                    break;
                }
            }
            
            if(!stop) {
                int free = 0, have = 1;
                for(int i = 0; i < k-1; i++) {
                    if(s[n-1-i] == '?')
                        free++;
                    else if(s[n-1-i] == s[0])
                        have++;
                }
                int need = (k+1)/2-have;
                for(int h = max(0, need); h <= free; h++) {
                    // cout << "end " << choose(free, h) << endl;
                    ways += choose(free, h);
                }
            }
            return ways;
        };
        
        // ll B = brute(n, k, s);
        mi res = 0;
        if(s[0] == '?') {
            s[0] = '0';
            res += solve();
            s[0] = '1';
            res += solve();
        }
        else
            res += solve();
        // if(res.val != B) {
            // cout << res << " " << B << endl;
            // cout << s << endl;
            // return -1;
        // }
        cout << res << "\n";
    }
}