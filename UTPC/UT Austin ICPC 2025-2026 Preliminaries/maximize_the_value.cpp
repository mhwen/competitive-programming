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

constexpr ll INF = -1e18;

struct ST {
    struct Node {
        ll sum = 0, p = 0, s = 0, best = 0;
    };
    Node EMPTY{0, 0, 0, -INF};
    int n;
    vector<Node> tree;
    ST(int _n) : n(_n), tree(4*n) {}
    Node merge(Node left, Node right) {
        if(left.best == -INF)
            return right;
        if(right.best == -INF)
            return left;
        Node res;
        res.sum = left.sum+right.sum;
        res.p = max(left.p, left.sum+right.p);
        res.s = max(right.s, right.sum+left.s);
        res.best = max(max(left.best, right.best), left.s+right.p);
        return res;
    }
    void set(Node& node, ll v) {
        node.sum = v;
        node.p = v;
        node.s = v;
        node.best = v;
    }
    
    void update(int curr, int l, int r, int p, ll v) {
        if(r < p || l > p)
            return;
        if(l == r) {
            assert(l==p);
            set(tree[curr], v);
            return;
        }
        int m = (l+r)/2;
        update(curr*2, l, m, p, v);
        update(curr*2+1, m+1, r, p, v);
        tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
    }
    void upd(int p, ll v) {
        update(1, 0, n-1, p, v);
    }
    Node query(int curr, int l, int r, int L, int R) {
        if(r < L || l > R)
            return EMPTY;
        if(L <= l && r <= R)
            return tree[curr];
        int m = (l+r)/2;
        Node left = query(curr*2, l, m, L, R);
        Node right = query(curr*2+1, m+1, r, L, R);
        return merge(left, right);
    }
    Node qry(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<pair<int, ll>>> lefts(n), rights(n);
        for(int i = 0; i < m; i++) {
            int l, r;
            ll v;
            cin >> l >> r >> v;
            l--; r--;
            lefts[l].pb({i, v});
            rights[r].pb({i, 0});
        }
        vector<ll> ans(q);
        vector<vector<pair<int, pair<int, int>>>> queries(n);
        for(int i = 0; i < q; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            l--; r--; k--;
            queries[k].pb({i, {l, r}});
        }
        ST tree(m);
        for(int i = 0; i < n; i++) {
            for(auto [p, v] : lefts[i])
                tree.upd(p, v);
            for(auto [id, lr] : queries[i]) {
                auto [l, r] = lr;
                ans[id] = tree.qry(l, r).best;
            }
            for(auto [p, v] : rights[i])
                tree.upd(p, v);
        }
        for(ll a : ans)
            cout << a << "\n";
    }
}