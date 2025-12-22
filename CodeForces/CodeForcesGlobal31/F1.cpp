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

constexpr int MX = 5005;

int main() {   
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<mi> ans(t);
    map<pair<int, int>, vector<int>> rowQueries;
    map<pair<int, int>, vector<int>> colQueries;
    for(int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        rowQueries[{n+1, m}].pb(i);
        colQueries[{n, m+1}].pb(i);
        ans[i] = mi(4).pow((n+1)*(m+1));
    }
    
    mi inv2 = mi(2).inv();
    mi inv3 = mi(3).inv();
    mi inv4 = mi(4).inv();
    
    vector<mi> pows(MX), invPows(MX);
    pows[0] = invPows[0] = 1;
    for(int i = 1; i < sz(pows); i++) {
        pows[i] = pows[i-1]*4;
        invPows[i] = invPows[i-1]*inv4;
    }
    
    vector<mi> down(MX);
    vector right(MX, vector<mi>(2));
    //0: left pointing
    //1: anything else
    
    vector<mi> colSum(MX);
    for(int r = 1; r < MX-1; r++) {
        vector<mi> rowSum(MX);
        vector<mi> newDown(MX);
        vector newRight(MX, vector<mi>(2));
        mi P1 = 1;
        mi P2 = pows[r-1];
        mi P1inv = 1;
        mi P2inv = invPows[r-1];
        for(int c = 1; c < MX-1; c++) {
            if(r == 2 && c == 1)
                down[1] = 4*4*3*3;
            if(r == 1 && c == 2) {
                right[2][0] = 4*4*3;
                right[2][1] = 4*3*2;
            }
            //D -> D
            newDown[c] += pows[c-1]*down[c]*3*3;
            
            //D -> R
            mi reduced = down[c]*inv3*2;
            right[c+1][0] += pows[c-1]*4*reduced;
            right[c+1][1] += pows[c-1]*2*reduced;
            
            reduced = right[c][1]*inv2;
            //R -> D
            newDown[c] += right[c][0]*pows[r]*3;
            newDown[c] += reduced*pows[r]*3;
            
            //R -> R
            right[c+1][0] += (right[c][0]+right[c][1])*3*pows[r-1];
            right[c+1][1] += reduced*2*3*pows[r-1];
            
            rowSum[c] += rowSum[c-1]+down[c]*P1inv;
            colSum[c] += (right[c][0]+right[c][1])*P2inv;
            if(rowQueries.count({r, c})) {
                for(auto id : rowQueries[{r, c}])
                    ans[id] -= rowSum[c]*P1;
            }
            if(colQueries.count({r, c})) {
                for(auto id : colQueries[{r, c}])
                    ans[id] -= colSum[c]*P2;
            }
            P1 *= pows[r];
            P2 *= pows[r-1];
            P1inv *= invPows[r];
            P2inv *= invPows[r-1];
        }
        swap(down, newDown);
        swap(right, newRight);
    }
    
    for(auto a : ans)
        cout << a << "\n";
}