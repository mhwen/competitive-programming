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

struct ST {
    int n;
    vector<int> tree;
    ST(int _n) : n(_n), tree(2*n) {}
    void update(int l, int r, int val) {
        l+=n; r+=n;
        while(l<=r) {
            if(l%2==1)
                tree[l++]^=val;
            if(r%2==0)
                tree[r--]^=val;
            l/=2;
            r/=2;
        }
    }
    int query(int p) {
        p+=n;
        int res = 0;
        while(p > 0) {
            res ^= tree[p];
            p/=2;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	ST tree(1<<21);
	
	auto addRange = [&](int l, int r, int M) {
	    l %= M;
	    r %= M;
	    l = (l+M)%M;
	    r = (r+M)%M;
	    if(l > r) {
	        tree.update(0, r, M/2);
	        tree.update(l, M-1, M/2);
	    }
	    else {
	        tree.update(l, r, M/2);
	    }
	};
	
	for(int i = 0; i < n; i++) {
	    int x;
	    cin >> x;
	    for(int M = 2; M <= (1<<21); M*=2) {
	        addRange(M/2-x, M-1-x, M);
	    }
	}
	while(q-->0) {
	    int t;
	    cin >> t;
	    if(t==1) {
	        int x;
	        cin >> x;
	        for(int M = 2; M <= (1<<21); M*=2) {
    	        addRange(M/2-x, M-1-x, M);
    	    }
	    }
	    else {
	        int v;
	        cin >> v;
	        int res = 0;
	        for(int M = 2; M <= (1<<21); M*=2) {
	            res ^= (M/2)&tree.query(v%M);
	        }
	        cout << res << "\n";
	    }
	}
}