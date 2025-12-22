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

struct st {
    int n;
    vector<int> tree;
    st(int _n) : n(_n), tree(2*n) {}
    void update(int p, int amt) {
        p += n;
        while(p > 0) {
            tree[p] += amt;
            p/=2;
        }
    }
    ll query(int l, int r) {
        l += n; r += n;
        ll res = 0;
        while(l <= r) {
            if(l%2==1)
                res += tree[l++];
            if(r%2==0)
                res += tree[r--];
            l/=2;
            r/=2;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	ll k;
	cin >> n >> k;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	
	auto check = [&](int t) {
	    int curr = 0;
	    ll amt = 0;
	    st tree(2*n+1);
	    tree.update(n, 1);
	    for(int i = 0; i < n; i++) {
	        int d = a[i]<=t ? -1 : 1;
	        curr += d;
	        amt += tree.query(curr+n+1, n+n);
	        tree.update(curr+n, 1);
	    }
	    return amt;
	};
	
	vector<int> coords = a;
	sort(all(coords));
	coords.resize(unique(all(coords))-coords.begin());
	int l = 0, r = sz(coords)-1;
	while(l <= r) {
	    int m = (l+r)/2;
	    if(check(coords[m]) < k)
	        l = m+1;
	    else
	        r = m-1;
	}
	cout << coords[l] << "\n";
}