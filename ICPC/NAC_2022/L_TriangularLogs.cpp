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
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

struct ST {
    int n;
    vector<vector<pii>> tree;
    ST(int _n) : n(_n), tree(2*n) {}
    void merge(vector<pii>& a, vector<pii>& b, vector<pii>& res) {
        int ai = 0, bi = 0;
        while(ai < sz(a) && bi < sz(b)) {
            if(a[ai].first < b[bi].first)
                res.pb(a[ai++]);
            else
                res.pb(b[bi++]);
        }
        while(ai < sz(a))
            res.pb(a[ai++]);
        while(bi < sz(b))
            res.pb(b[bi++]);
    }
    void build(vector<vector<pii>>& coords) {
        for(int i = 2*n-1; i > 0; i--) {
            if(i >= n) {
                sort(all(coords[i-n]));
                for(auto v : coords[i-n])
                    tree[i].pb(v);
            }
            else
                merge(tree[2*i], tree[2*i+1], tree[i]);
        }
    }
    vector<int> query(int l, int r, int loy, int hiy) {
        l+=n; r+=n;
        vector<int> res;
        while(l<=r) {
            if(l%2==1) {
                auto it = lower_bound(all(tree[l]), pair{loy, 0});
                while(it != tree[l].end() && sz(res) < 100 && it->first <= hiy) {
                    res.pb(it->second);
                    it++;
                }
                l++;
            }
            if(r%2==0) {
                auto it = lower_bound(all(tree[r]), pair{loy, 0});
                while(it != tree[r].end() && sz(res) < 100 && it->first <= hiy) {
                    res.pb(it->second);
                    it++;
                }
                r--;
            }
            l/=2;
            r/=2;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> xC;
	vector<int> yC;
	vector<int> tx(n), ty(n), th(n);
	for(int i = 0; i < n; i++) {
	    cin >> tx[i] >> ty[i] >> th[i];
	    xC.pb(tx[i]);
	    yC.pb(ty[i]);
	}
	vector<int> xlo(q), xhi(q), ylo(q), yhi(q);
	for(int i = 0; i < q; i++) {
	    cin >> xlo[i] >> ylo[i] >> xhi[i] >> yhi[i];
	    xC.pb(xlo[i]);
	    xC.pb(xhi[i]);
	    yC.pb(ylo[i]);
	    yC.pb(yhi[i]);
	}
	sort(all(xC));
	xC.erase(unique(all(xC)), xC.end());
	sort(all(yC));
	yC.erase(unique(all(yC)), yC.end());
	auto compX = [&](int X) {
	    return (int)(lower_bound(all(xC), X)-xC.begin());
	};
	auto compY = [&](int Y) {
	    return (int)(lower_bound(all(yC), Y)-yC.begin());
	};
	vector<vector<pii>> coords(sz(xC));
	for(int i = 0; i < n; i++) {
	    int X = compX(tx[i]);
	    int Y = compY(ty[i]);
	    coords[X].pb({Y, th[i]});
	}
	ST tree(sz(xC));
	tree.build(coords);
	for(int i = 0; i < q; i++) {
	    int Xlo = compX(xlo[i]);
	    int Xhi = compX(xhi[i]);
	    int Ylo = compY(ylo[i]);
	    int Yhi = compY(yhi[i]);
	    auto res = tree.query(Xlo, Xhi, Ylo, Yhi);
	    if(sz(res) >= 100)
	        cout << 1 << "\n";
	    else {
	        sort(all(res));
	        int good = 0;
	        for(int j = 0; j < sz(res)-2; j++) {
	            if(res[j]+res[j+1] > res[j+2]) {
	                good = 1;
	                break;
	            }
	        }
	        cout << good << "\n";
	    }
	}
	
}