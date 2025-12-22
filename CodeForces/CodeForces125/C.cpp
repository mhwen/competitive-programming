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
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr double PI = acos(-1);
constexpr double EPS = 1e-9;

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
	double angle() const { 
		double a = atan2(y, x);
		if(a < 0)
			a += 2*PI;
		return a;
	}
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<double> P;

vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.pb({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}

vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

bool onSegment(P s, P e, P p) {
	return segDist(s,e,p) <= EPS;
}

vector<P> circleSegment(P c, double r, P a, P b) {
	auto line = circleLine(c, r, a, b);
	vector<P> res;
	for(auto p : line)
		if(onSegment(a, b, p))
			res.push_back(p);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	P them, me;
	double theirV, myV, R;
	cin >> them.x >> them.y >> theirV >> me.x >> me.y >> myV >> R;
	double theirR = them.dist();
	auto arcLen = [&](P a, P b) {
		double da = abs(a.angle()-b.angle());
		da = min(da, 2*PI-da);
		return da*R;
	};
	
	auto check = [&](double t) {
		P newThem = them.rotate((theirV*t)/theirR);
		if(circleSegment(P(0,0), R, me, newThem).empty())
			return (newThem-me).dist()/myV <= t;	
		else {
			auto myTan = tangents(P(0,0), R, me, 0);
			auto theirTan = tangents(P(0,0), R, newThem, 0);
			assert(sz(myTan) && sz(theirTan));
			double dist = (myTan[0].first-me).dist() + (theirTan[0].first-newThem).dist();
			double best = 2*PI*R;
			for(auto myT : myTan)
				for(auto theirT : theirTan)
					best = min(best, arcLen(myT.first, theirT.first));
			return (dist+best)/myV <= t;
		}
	};
	
	double l = 0, r = 1e6;
	for(int i = 0; i < 200; i++) {
		double mid = (l+r)/2;
		if(check(mid))
			r = mid;
		else
			l = mid;
	}
	cout << fixed << setprecision(20) << (l+r)/2 << "\n";
}