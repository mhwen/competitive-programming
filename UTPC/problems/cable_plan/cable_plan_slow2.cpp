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
	bool operator<(P p) const { return tie(x,y)<tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	bool half() const { return y < 0 || (y == 0 && x < 0); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
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

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return abs((double)(b-a).cross(p-a)/(b-a).dist());
}

template<class P>
double lineDist(ld A, ld B, ld C, const P& p) {
    Point<ld> a, b, pp(p.x, p.y);
    //Ax + By + C = 0
    //By = -C-Ax
    //Ax = -C-By
    if(B == 0) {
        assert(A != 0);
        a = Point<ld>(-C/A, 0);
        b = Point<ld>((-C-B)/A, 1);
    }
    else {
        a = Point<ld>(0, -C/B);
        b = Point<ld>(1, (-C-A)/B);
    }
    return lineDist(a, b, pp);
}

typedef Point<ll> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<P> p(n);
	for(int i = 0; i < n; i++) {
	    int x, y;
	    cin >> x >> y;
	    p[i] = P(x, y);
	}
	
	vector<P> hull = convexHull(p);
	
	cout << fixed << setprecision(10);
	while(q-->0) {
	    int A, B, C;
	    cin >> A >> B >> C;
	    double d = 0;
	    for(auto& pp : p)
	        d = max(d, lineDist(A, B, C, pp));
	    cout << d << "\n";
	}
}