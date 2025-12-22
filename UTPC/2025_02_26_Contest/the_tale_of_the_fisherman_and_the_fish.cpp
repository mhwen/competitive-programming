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


struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	ll s;
	Node(int v) : val(v), y(rand()), s(v) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sum(Node* n) { return n ? n->s : 0LL; }
void Node::recalc() { 
    int lC = cnt(l);
    ll lS = sum(l);
    int rC = cnt(r);
    ll rS = sum(r);
    if(lC%2==0)
        s = lS+val-rS;
    else
        s = lS-val+rS;
    c = lC+rC+1;
}

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	Node* treap = new Node(a[0]);
	for(int i = 1; i < n; i++) {
	    treap = ins(treap, new Node(a[i]), i);
	}
	
	auto print = [](ll v) {
	    if(v == 0)
	        cout << "TIE\n";
	    else if(v > 0)
	        cout << "FISH\n";
	    else
	        cout << "MAN\n";
	};
	while(q-->0) {
	    int l, r;
	    cin >> l >> r;
	    l--; r--;
	    move(treap, l, l+1, r+1);
	    print(treap->s);
	}
}