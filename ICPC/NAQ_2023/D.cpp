#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>


using namespace std;

typedef long long ll;
typedef long double ld;


template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T xx=0, T yy=0) : x(xx), y(yy) {}
	P operator+ (P p) const { return P(x+p.x, y+p.y);}
	P operator- (P p) const { return P(x-p.x, y-p.y);}
	P operator* (T d) const { return P(x*d, y*d);}
	P operator/ (T d) const { return P(x/d, y/d);}
	T dot(P p) const { return x*p.x + y*p.y;}
	T cross(P p) const { return x*p.y - y*p.x;}
	ld dist2() const { return x*x+y*y;}
};


typedef Point<ld> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))


ld circlePoly(P c, ld r, vector<P> ps) {
	auto tri = [&](P p, P q) {
		auto r2 = r*r/2;
		P d = q-p;
		auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		auto det = a*a-b;
		if(det <= 0)	return arg(p, q)*r2;
		auto s = max((ld)0., -a-sqrt(det)), t = min((ld)1., -a+sqrt(det));
		if(t < 0 || 1 <= s) return arg(p, q)*r2;
		P u = p+d*s, v = p+d*t;
		return arg(p, u)*r2 + u.cross(v)/2 + arg(v, q) * r2;
	};
	ld sum = 0.0;
	for(int i = 0; i < (int)ps.size(); i++) {
		sum += tri(ps[i] - c, ps[(i+1)%((int)ps.size())] - c);
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, r, w, h;
	cin >> n >> r >> w >> h;
	vector<Point<ld>> points(n);
	vector<int> val(n);

	
	vector<Point<ld>> rect;
	rect.push_back(Point<ld>(0, 0));
	rect.push_back(Point<ld>(w, 0));
	rect.push_back(Point<ld>(w, h));
	rect.push_back(Point<ld>(0, h));
	ld ans = 0;
	for(int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y >> val[i];
		ld area = circlePoly(points[i], r, rect);
		ans += area/(w*h)*val[i];
	}

	cout << setprecision(20) << ans << "\n";
	

	
}