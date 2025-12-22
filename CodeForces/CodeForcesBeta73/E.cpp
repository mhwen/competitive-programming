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
typedef vector<int> vi;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	bool half() const { return y < 0 || (y == 0 && x < 0); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;
void reorder_polygon(vector<P> &p) {
	int pos = 0;
	for (int i = 1; i < sz(p); i++) {
		if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
			pos = i;
	}
	rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski(vector<P> p, vector<P> q) {
	reorder_polygon(p);
	reorder_polygon(q);

	p.pb(p[0]);
	p.pb(p[1]);
	q.pb(q[0]);
	q.pb(q[1]);

	vector<P> result;
	int i = 0, j = 0;
	while (i < sz(p) - 2 || j < sz(q) - 2) {
		result.pb(p[i] + q[j]);
		auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
		if (cross >= 0 && i < sz(p) - 2) ++i;
		if (cross <= 0 && j < sz(q) - 2) ++j;
	}
	return result;
}

template<class P>
bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

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
	vector<vector<P>> poly(3);
	for(int i = 0; i < 3; i++) {
		int n;
		cin >> n;
		poly[i] = vector<P>(n);
		for(int j = 0; j < n; j++) {
			cin >> poly[i][j].x >> poly[i][j].y;
		}
	}
	vector<P> hull = minkowski(minkowski(poly[0], poly[1]), poly[2]);
	int m;
	cin >> m;
	while(m-->0) {
		P p;
		cin >> p.x >> p.y;
		p.x *= 3;
		p.y *= 3;
		if(inHull(hull, p, false))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}