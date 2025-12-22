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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

typedef uint64_t ull;
struct H {
	ull x; H(ull _x=0) : x(_x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator!=(H o) const { return get() != o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3;

struct HashInterval {
	vector<H> ha, pw, revHa;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha), revHa(sz(str)+1) {
		pw[0] = 1;
		for(int i = 0; i < sz(str); i++) {
		    revHa[sz(str)-1-i] = revHa[sz(str)-i] * C + str[sz(str)-1-i];
			ha[i+1] = ha[i] * C + str[i];
			pw[i+1] = pw[i] * C;
		}
	}
	//inclusive
	H get(int a, int b) {
	    if(b < a) {
	        return H(0);
	    }
		return ha[b+1] - ha[a] * pw[b+1 - a];
	}
	H getRev(int a, int b) {
	    if(b < a) {
	        return H(0);
	    }
		return revHa[a] - revHa[b+1] * pw[b+1 - a];
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector<string> s(n);
    vector<HashInterval> hashes;
    map<H, vector<H>> prefixes, suffixes;
    map<H, ll> cnts, revCnts;
    vector<int> lens;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        hashes.emplace_back(s[i]);
        for(int j = 0; j < sz(s[i])-1; j++) {
            prefixes[hashes[i].getRev(0, j)].pb(hashes[i].getRev(j+1, sz(s[i])-1));
            suffixes[hashes[i].get(j+1, sz(s[i])-1)].pb(hashes[i].get(0, j));
        }
        cnts[hashes[i].get(0, sz(s[i])-1)]++;
        revCnts[hashes[i].getRev(0, sz(s[i])-1)]++;
        lens.pb(sz(s[i]));
    }
    sort(all(lens));
    lens.erase(unique(all(lens)), lens.end());
    ll mirrors = 0;
    for(auto& [hash, cnt] : cnts) {
        mirrors += cnt*revCnts[hash];
    }
    map<H, ll> prefixContrib, suffixContrib;
    for(auto& [hash, v] : prefixes) {
        for(auto& remHash : v) {
            prefixContrib[hash] += cnts[remHash];
        }
    }
    for(auto& [hash, v] : suffixes) {
        for(auto& remHash : v) {
            suffixContrib[hash] += revCnts[remHash];
        }
    }
    
    ll ans = 0;
    for(int i = 0; i < sz(s); i++) {
        for(int mid = 0; mid < sz(s[i]); mid++) {
            int leftSz = mid;
            int rightSz = sz(s[i])-1-mid;
            if(leftSz < rightSz && hashes[i].get(0, mid-1) == hashes[i].getRev(mid+1, mid+1+leftSz-1)) {
                H R = hashes[i].getRev(mid+1+leftSz, sz(s[i])-1);
                ans += suffixContrib[R];
                for(int l : lens) {
                    if(l >= rightSz)
                        break;
                    ll A = cnts[hashes[i].getRev(mid+1+leftSz, mid+1+leftSz+l-1)];
                    ll B = cnts[hashes[i].getRev(mid+1+leftSz+l, sz(s[i])-1)];
                    ans += A*B;
                }
            }
            else if(leftSz > rightSz && hashes[i].get(mid-rightSz, mid-1) == hashes[i].getRev(mid+1, sz(s[i])-1)) {
                H L = hashes[i].get(0, mid-rightSz-1);
                ans += prefixContrib[L];
                for(int l : lens) {
                    if(l >= leftSz)
                        break;
                    ll A = revCnts[hashes[i].get(0, l-1)];
                    ll B = revCnts[hashes[i].get(l, mid-rightSz-1)];
                    ans += A*B;
                }
            }
            else if(leftSz == rightSz && hashes[i].get(0, mid-1) == hashes[i].getRev(mid+1, sz(s[i])-1)){                
                ans += mirrors;
            }
        }
    }
    cout << ans << "\n";
}