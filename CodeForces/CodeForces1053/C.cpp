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

constexpr ll INF = 1e18;

struct ST {
    struct Node {
        ll v = 0, lazy = 0;
        Node() {}
        Node(ll _v) : v(_v) {}
    };
    Node EMPTY{-INF};
    
    int n;
    vector<Node> tree;
    ST(int _n) : n(_n), tree(4*n) {}
    ST(int _n, const vector<ll>& a) : ST(_n) {
        build(1, 0, n-1, a);
    }
    
    void build(int curr, int l, int r, const vector<ll>& a) {
        if(l == r) {
            tree[curr] = Node(a[l]);
            return;
        }
        int m = (l+r)/2;
        build(curr*2, l, m, a);
        build(curr*2+1, m+1, r, a);
        tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
    }
    
    void push(int i) {
        tree[i*2] = add(tree[i*2], tree[i].lazy);
        tree[i*2+1] = add(tree[i*2+1], tree[i].lazy);
        tree[i].lazy = 0;
    }
    
    Node merge(const Node& left, const Node& right) {
        return Node(max(left.v, right.v));
    }
    
    template <typename F>
    void update(int curr, int l, int r, int L, int R, F op) {
        if(r < L || l > R)
            return;
        if(L <= l && r <= R) {
            tree[curr] = op(tree[curr]);
            return;
        }
        push(curr);
        int m = (l+r)/2;
        update(curr*2, l, m, L, R, op);
        update(curr*2+1, m+1, r, L, R, op);
        tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
    }
    
    Node add(Node a, ll v) {
        a.v += v;
        a.lazy += v;
        return a;
    };
    
    void upd_add(int L, int R, ll v) {
        auto addF = [this, v](Node a) {
            return add(a, v);
        };
        update(1, 0, n-1, L, R, addF);
    }
    
    void upd_set(int p, ll v) {
        auto setF = [this, v](Node a) {
            a.v = max(a.v, v);
            return a;
        };
        update(1, 0, n-1, p, p, setF);
    }
    
    Node query(int curr, int l, int r, int L, int R) {
        if(r < L || l > R)
            return EMPTY;
        if(L <= l && r <= R)
            return tree[curr];
        push(curr);
        int m = (l+r)/2;
        Node left = query(curr*2, l, m, L, R);
        Node right = query(curr*2+1, m+1, r, L, R);
        return merge(left, right);
    }
    
    ll qry(int L, int R) {
        return query(1, 0, n-1, L, R).v;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> v(n);
        for(int i = 0; i < n; i++)
            cin >> v[i];
        
        vector<int> a(n), b(n);
        vector<int> bPos(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            b[i]--;
            bPos[b[i]] = i;
        }
        ST tree(n+1);
        for(int i = 0; i < n; i++) {
            int p = bPos[a[i]]+1;
            tree.upd_set(p, tree.qry(0, p-1));
            tree.upd_add(0, p-1, v[a[i]]);
        }
        cout << tree.qry(0, n) << "\n";
    }
}