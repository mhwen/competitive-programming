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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	bool operator<(P p) const { return tie(x,y)<tie(p.x,p.y); }
	bool half() const { return y<0 || (y==0 && x<0); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

vector<P> minkowski(vector<vector<P>>& hulls) {
	P curr(0, 0);
	vector<P> slopes;
	for(auto& ps : hulls) {
		P lo = ps[0];
		if(sz(ps) > 1) {
			P prev = ps.back();
			for(auto p : ps) {
				slopes.push_back(p-prev);
				if(p.y < lo.y || (p.y==lo.y && p.x<lo.x))
					lo = p;
				prev = p;
			}
		}
		curr = curr+lo;
	}
	if(slopes.empty()) return vector<P>{curr};
	
	sort(all(slopes), [](P a, P b) {
		return a.half()==b.half() ? a.cross(b)>0 : a.half()<b.half();
	});
	vector<P> sum;
	P prev(0, 0);
	for(auto s : slopes) {
		if(!(s.cross(prev)==0 && s.dot(prev)>0))
			sum.push_back(curr);
		curr = curr+s;
		prev = s;
	}
	return sum;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> x1(n);
	vector<ll> y1(n);
	vector<ll> x2(n);
	vector<ll> y2(n);
	for(int i = 0; i < n; i++) {
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
	}
	
	auto check = [&](vector<P> a, vector<P> b) {
		a = convexHull(a);
		b = convexHull(b);
		for(int i = 0; i < sz(b); i++) {
			b[i] = P(0,0)-b[i];
		}
		vector<vector<P>> tot{a,b};
		auto res = minkowski(tot);
		return !inHull(res, P(0,0));
	};
	vector<P> topRight(n);
	vector<P> bottomLeft(n);
	vector<P> topLeft(n);
	vector<P> bottomRight(n);
	for(int i = 0; i < n; i++) {
		topRight[i] = P(x2[i], y2[i]);
		topLeft[i] = P(x1[i], y2[i]);
		bottomRight[i] = P(x2[i], y1[i]);
		bottomLeft[i] = P(x1[i], y1[i]);
	}
	if(check(topRight, bottomLeft) || check(topLeft, bottomRight))
		cout << "possible\n";
	else
		cout << "impossible\n";
	
}