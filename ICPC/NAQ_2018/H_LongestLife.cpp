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

struct Line {
	mutable ld k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	ld inf = (ld)1/.0;
	ld div(ld a, ld b) {
		return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ld k, ld m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ld query(ld x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ld n;
	cin >> n;
	int p;
	ld c;
	cin >> p >> c;
	LineContainer curr;
	curr.add(-1, n);
	for(int i = 0; i < p; i++) {
		ld t, x, y;
		cin >> t >> x >> y;
		ld slope = -y/x;
		ld best = curr.query(t);
		if(best-c >= 0) {
			ld intercept = best-c-slope*t;
			curr.add(slope, intercept);
		}
	}
	ld l = 0, r = 1e18;
	for(int i = 0; i < 100; i++) {
		ld mid = (l+r)/2;
		if(curr.query(mid) > 0)
			l = mid;
		else
			r = mid;
	}
	cout << fixed << setprecision(20) << (l+r)/2 << "\n";
}