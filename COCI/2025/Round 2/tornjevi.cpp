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

struct ST {
    struct Node {
        int p=0, s=0, tot=0, best=0;  
    };
    Node merge(Node L, Node R) {
        Node res;
        res.p = max(L.p, L.tot+R.p);
        res.s = max(R.s, R.tot+L.s);
        res.tot = L.tot+R.tot;
        res.best = max(L.s+R.p, max(L.best, R.best));
        return res;
    }
    int n;
    vector<Node> tree;
    ST(vector<int>& a) {
        n = 1;
        while(n < sz(a))
            n*=2;
        tree.resize(2*n);
        for(int i = 2*n-1; i > 0; i--) {
            if(i >= n) {
                if(i-n < sz(a))
                    tree[i] = Node{a[i-n], a[i-n], a[i-n], a[i-n]};
            }
            else
                tree[i] = merge(tree[i*2], tree[i*2+1]);
        }
    }
    Node query(int l, int r) {
        l+=n; r+=n;
        Node L, R;
        while(l <= r) {
            if(l%2==1)
                L = merge(L, tree[l++]);
            if(r%2==0)
                R = merge(tree[r--], R);
            l/=2;
            r/=2;
        }
        return merge(L, R);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        if(s[i] == 'P')
            a[i] = 1;
        else
            a[i] = -1;
    }
    ST tree1(a);
    for(int i = 0; i < n; i++)
        a[i] *= -1;
    ST tree2(a);
    while(q-->0) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int res1 = tree1.query(l, r).best;
        int res2 = tree2.query(l, r).best;
        cout << max(res1, res2) << "\n";
    }
}