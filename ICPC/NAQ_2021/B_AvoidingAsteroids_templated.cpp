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

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ld INF = 1e15;

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T _x=0, T _y=0, T _z=0) : x(_x), y(_y), z(_z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	ld dist() const { return sqrt((ld)dist2()); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
};


#include "Point3D.h"

typedef Point3D<ld> P;
//returns closest two points from each 3d segment
pair<P, P> segmentDistance3d(P s1, P e1, P s2, P e2) {
	pair<P, P> res{s1, s2};
	auto check = [&res](P a, P b) {
		if((b-a).dist() < (res.second-res.first).dist())
			res = {a, b};
	};
	//check endpoint-endpoint
	check(s1, s2);
	check(s1, e2);
	check(e1, s2);
	check(e1, e2);

	P d1 = (e1-s1).unit();
	ld t1Max = (e1-s1).dist();
	P d2 = (e2-s2).unit();
	ld t2Max = (e2-s2).dist();
	//check endpoint-segment, dist from p to the line segment s + t*d
	auto pointLine = [&](P p, P s, P d, ld tMax) {
		P v = p-s;
		ld t = v.dot(d);
		if(0 <= t && t <= tMax)
			check(s+d*t, p);
	};
	pointLine(s1, s2, d2, t2Max);
	pointLine(e1, s2, d2, t2Max);
	pointLine(s2, s1, d1, t1Max);
	pointLine(e2, s1, d1, t1Max);
	
	//check segment-segment
	P n = d1.cross(d2);
	if(n.dist2() != 0) { //only check if not parallel; parallel case is handled by pointLine checks
		ld t1 = (d2.cross(n)).dot(s2-s1)/n.dot(n);
		ld t2 = (d1.cross(n)).dot(s2-s1)/n.dot(n);
		if(0 <= t1 && t1 <= t1Max && 0 <= t2 && t2 <= t2Max)
			check(s1+d1*t1, s2+d2*t2);
	}
	return res;
}

struct Asteroid {
	P p, dir;
	ld r;
	Asteroid() {}
	Asteroid(P pp, P d, ld R) : p(pp), dir(d.unit()), r(R) {}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	P A, B;
	cin >> A.x >> A.y >> A.z >> B.x >> B.y >> B.z;

	bool good = true;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		P p, d;
		cin >> p.x >> p.y >> p.z >> d.x >> d.y >> d.z;
		ld r = 0;
		int m;
		cin >> m;
		while(m-->0) {
			P q;
			cin >> q.x >> q.y >> q.z;
			r = max(r, (q-p).dist());
		}
		auto res = segmentDistance3d(A, B, p, p+d*INF);
		if((res.second-res.first).dist() <= r)
			good = false;
	}
	if(good)
		cout << "Go\n";
	else
		cout << "Surrender\n";
}