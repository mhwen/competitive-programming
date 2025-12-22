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

constexpr int INF = 1e9;

struct ST_lazy {
    int n;
    vector<int> tree, lazy;
    ST_lazy(int _n) : n(_n), tree(4*n), lazy(4*n) {}
    void push(int v) {
        tree[2*v] += lazy[v];
        tree[2*v+1] += lazy[v];
        lazy[2*v] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    void update(int l, int r, int amt) {
        update(1, 0, n-1, l, r, amt);
    }
    void update(int v, int l, int r, int L, int R, int amt) {
        if(r < L || l > R)
            return;
        if(L <= l && r <= R) {
            tree[v] += amt;
            lazy[v] += amt;
        }
        else {
            int m = (l+r)/2;
            push(v);
            update(2*v, l, m, L, R, amt);
            update(2*v+1, m+1, r, L, R, amt);
            tree[v] = min(tree[2*v], tree[2*v+1]);
        }
    }
    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
    int query(int v, int l, int r, int L, int R) {
        if(r < L || l > R)
            return INF;
        if(L <= l && r <= R)
            return tree[v];
        else {
            int m = (l+r)/2;
            push(v);
            return min(query(2*v, l, m, L, R), query(2*v+1, m+1, r, L, R));
        }
    }
    int walkLeft(int p) {
        return walkLeft(1, 0, n-1, p);
    }
    int walkLeft(int v, int l, int r, int p) {
        if(l > p || tree[v] > 0)
            return -1;
        if(l == r)
            return l;
        else {
            push(v);
            int m = (l+r)/2;
            int close = walkLeft(2*v+1, m+1, r, p);
            if(close != -1)
                return close;
            return walkLeft(2*v, l, m, p);
        }
    }
    int walkRight(int p) {
        return walkRight(1, 0, n-1, p);
    }
    int walkRight(int v, int l, int r, int p) {
        if(r < p || tree[v] > 0)
            return -1;
        if(l == r)
            return l;
        else {
            push(v);
            int m = (l+r)/2;
            int close = walkRight(2*v, l, m, p);
            if(close != -1)
                return close;
            return walkRight(2*v+1, m+1, r, p);
        }
    }
};

struct ST {
    int n;
    vector<int> tree;
    ST(int _n): n(_n), tree(2*n, INF) {}
    void update(int p, int v) {
        p += n;
        tree[p] = v;
        p/=2;
        while(p > 0) {
            tree[p] = min(tree[2*p], tree[2*p+1]);
            p/=2;
        }
    }
    int query(int l, int r) {
        int res = INF;
        l+=n; r+=n;
        while(l <= r) {
            if(l%2==1)
                res = min(res, tree[l++]);
            if(r%2==0)
                res = min(res, tree[r--]);
            l/=2;
            r/=2;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, m;
	    cin >> n >> m;
	    ST_lazy dead(n);
	    vector<multiset<int>> rights(n);
	    for(int i = 0; i < n; i++)
	        rights[i].insert(INF);
	    ST intervals(n);
	    vector<int> x(m), a(m), b(m);
	    for(int i = 0; i < m; i++) {
	        cin >> x[i] >> a[i] >> b[i];
	        a[i]--;
	        b[i]--;
	    }
	    
	    auto add = [&](int i) {
	        if(x[i] == 0)
	            dead.update(a[i], b[i], 1);
	        else {
	            rights[a[i]].insert(b[i]);
	            intervals.update(a[i], *rights[a[i]].begin());
	        }
	    };
	    
	    auto check = [&](int i) {
	        if(i >= m)
	            return false;
	        if(x[i] == 0) {
	            int l = dead.walkLeft(a[i]-1);
	            int r = dead.walkRight(b[i]+1);
	            if(r == -1)
	                r = n;
	            return intervals.query(l+1, r-1) > r-1;
	        }
	        else
	           return dead.query(a[i], b[i]) == 0;
	    };
	    
	    auto remove = [&](int i) {
	        if(x[i] == 0)
	            dead.update(a[i], b[i], -1);
	        else {
	            rights[a[i]].erase(rights[a[i]].find(b[i]));
	            intervals.update(a[i], *rights[a[i]].begin());
	        }
	    };
	    
	    vector<int> ans(m);
	    int right = 0;
	    for(int left = 0; left < m; left++) {
	        while(check(right))
	            add(right++);
	        ans[left] = right-1;
	        remove(left);
	    }
	    int q;
	    cin >> q;
	    while(q-->0) {
	        int l, r;
	        cin >> l >> r;
	        l--; r--;
	        if(r <= ans[l])
	            cout << "YES\n";
	        else
	            cout << "NO\n";
	    }
	}
}