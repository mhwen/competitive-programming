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
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	P o(0, 0);
	int n, m;
	cin >> n >> m;
	vector<P> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	vector<P> c(m);
	for(int i = 0; i < m; i++) {
		cin >> c[i].x >> c[i].y;
		c[i] = o-c[i];
	}
	auto res = minkowski(a, c);
	double time = 1e18;
	for(int i = 0; i < sz(res); i++) {
		int nxt = (i+1)%sz(res);
		time = min(time, lineDist(res[i], res[nxt], o));
	}
	cout << fixed << setprecision(20) << max(0., time-60) << "\n";
}