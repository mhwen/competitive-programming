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

constexpr ld INF = 1e18;

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

typedef Point3D<ld> P;

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
	P me = A;
	P myDir = (B-A).unit();
	ld myT = (B-A).dist();
	
	bool good = true;
	
	auto check = [&](Asteroid a) {
		ld r = a.r;
		auto po = [&](P p, P q) {
			if((p-q).dist() <= r)
				good = false;
		};
		//dist from p to the line segment s + t*dir
		auto pl = [&](P p, P s, P dir, ld tLimit) {
			P v = p-s;
			ld scale = v.dot(dir);
			if(0 <= scale && scale <= tLimit) {
				P res = s+dir*scale;
				po(res, p);
			}
		};
		//dist between two line segments of form s + t*dir, from [0, tLimit]
		auto line = [&](P s1, P dir1, ld t1Limit, P s2, P dir2, ld t2Limit) {
			P n = dir1.cross(dir2);
			//parallel
			if(n.dist2() == 0)
				return;
			ld t1 = (dir2.cross(n)).dot(s2-s1)/n.dot(n);
			ld t2 = (dir1.cross(n)).dot(s2-s1)/n.dot(n);
			if(0 <= t1 && t1 <= t1Limit && 0 <= t2 && t2 <= t2Limit) {
				P p1 = s1+dir1*t1;
				P p2 = s2+dir2*t2;
				po(p1, p2);
			}
		};
		
		po(a.p, A);
		po(a.p, B);
		pl(a.p, me, myDir, myT);
		pl(A, a.p, a.dir, INF);
		pl(B, a.p, a.dir, INF);
		line(a.p, a.dir, INF, me, myDir, myT);
	};
	
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
		check(Asteroid(p, d, r));
	}
	if(good)
		cout << "Go\n";
	else
		cout << "Surrender\n";
}