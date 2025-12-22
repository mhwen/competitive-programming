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

constexpr ld EPS = 1e-9;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	P unit() const { return *this/dist(); } // makes dist()=1
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
	return abs(p.cross(s, e)) <= EPS && (s - p).dot(e - p) <= EPS;
}

template<class P>
vector<P> circleLine(P c, ld r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	ld s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

typedef Point<ld> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	P p;
	cin >> p.x >> p.y;
	int n;
	cin >> n;
	vector<P> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i].x >> a[i].y;
	P q;
	cin >> q.x >> q.y;
	int m;
	cin >> m;
	vector<P> b(m);
	for(int i = 0; i < m; i++)
		cin >> b[i].x >> b[i].y;
	ld r = (q-p).dist();
	bool found = false;
	for(P bb : b) {
		for(int i = 0; i < sz(a); i++) {
			P from = a[i];
			P to = a[(i+1)%sz(a)];
			P c = p+bb-q;
			auto inter = circleLine(c, r, from, to);
			for(auto I : inter)
				if(onSegment(from, to, I))
					found = true;
		}
	}
	swap(a, b);
	swap(p, q);
	for(P bb : b) {
		for(int i = 0; i < sz(a); i++) {
			P from = a[i];
			P to = a[(i+1)%sz(a)];
			P c = p+bb-q;
			auto inter = circleLine(c, r, from, to);
			for(auto I : inter)
				if(onSegment(from, to, I))
					found = true;
		}
	}
	if(found)
		cout << "YES\n";
	else
		cout << "NO\n";
}