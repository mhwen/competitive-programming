#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;
typedef long long ll;
typedef long double ld;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

constexpr ld EPS = 1e-5;

template <class T> int sgn(T x) { return (x > 0) - (x < 0);}
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const {return (p-*this).dist() < EPS; }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2());}
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";}
};

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if(onSegment(c, d, a)) s.insert(a);
	if(onSegment(c, d, b)) s.insert(b);
	if(onSegment(a, b, c)) s.insert(c);
	if(onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, r;
	cin >> n >> m >> r;
	
	auto inCircle = [&](Point<ld> p) {
		return p.dist()<r;
	};
	
	vector<Point<ld>> candles(n);
	for(int i = 0; i < n; i++) {
		ld x, y;
		cin >> x >> y;
		candles[i] = Point(x, y);
	}
	vector<pair<Point<ld>, Point<ld>>> lines(m);
	for(int i = 0; i < m; i++) {
		ld a, b, c;
		cin >> a >> b >> c;
		if(b == 0) {
			lines[i].first = Point<ld>(-c/a, -1000);
			lines[i].second = Point<ld>(-c/a, 1000);
		}
		else {
			lines[i].first = Point<ld>(-1000, (-c+a*1000)/b);
			lines[i].second = Point<ld>(1000, (-c-a*1000)/b);
		}
	}
	ll pieces = 1;
	for(int i = 0; i < m; i++) {
		Point<ld> a = lines[i].first;
		Point<ld> b = lines[i].second;
		pieces++;
		vector<Point<ld>> intersections;
		for(int j = 0; j < i; j++) {
			Point<ld> c = lines[j].first;
			Point<ld> d = lines[j].second;
			auto res = segInter(a, b, c, d);
			if(res.empty())
				continue;
			Point<ld> in = res[0];
			if(inCircle(in)) {
				pieces++;
			}
		}
	}
	if(pieces != n) {
		cout << "no\n";
	}
	else {
		bool good = true;
		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				Point<ld> a = candles[i];
				Point<ld> b = candles[j];
				bool found = false;
				for(auto line : lines) {
					Point<ld> c = line.first;
					Point<ld> d = line.second;
					auto res = segInter(a, b, c, d);
					if(!res.empty())
						found = true;
				}
				if(!found)
					good = false;
			}
		}
		if(!good)
			cout << "no\n";
		else
			cout << "yes\n";
	}
}