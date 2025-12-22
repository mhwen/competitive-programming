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
#define double long double
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


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
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
bool compPoint(P a, P b) {
	return a.half() == b.half() ? a.cross(b) > 0 : a.half() < b.half();
}

template<class P>
void angleSort(vector<pair<P, int>> &v) {
	sort(all(v), [](pair<P, int> a, pair<P, int> b) {
	    if(compPoint(a.first, b.first))
	        return true;
	    if(compPoint(b.first, a.first))
	        return false;
	    return a.second > b.second;
	});
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

typedef Point<ll> PL;
typedef Point<double> PD;

constexpr double EPS = 1e-9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	
	auto inBounds = [&](PD p) {
	    return p.x >= -EPS && p.y >= -EPS && p.x <= n+EPS && p.y <= n+EPS;
	};
	
	auto getArea = [&](PD s, PD t) {
        vector<PD> pts{PD(0,0), PD(n,0), PD(n,n), PD(0,n)};
        vector<PD> poly;
        for(int i = 0; i < 4; i++) {
          if(s.cross(t, pts[i]) <= EPS)
              poly.pb(pts[i]);
          PD a = pts[i];
          PD b = pts[(i+1)%4];
          auto [cnt, inter] = lineInter(s, t, a, b);
          if(cnt == 1 && inBounds(inter) && s.cross(t, inter) <= EPS)
              poly.pb(inter);
        }
        return abs(polygonArea2(poly))/2;
	};
	
	
	vector<PL> p(m);
	vector<PD> pd(m);
	auto getCookies = [&](PD s, PD t) {
	    int cnt = 0;
	    for(auto& pp : pd) {
	        if(s.cross(t, pp) <= EPS)
	            cnt++;
	    }
	    return cnt;
	};
	
	double ans = 0;
	
	auto check = [&](PD s, PD t) {
	    double area = getArea(s, t);
	    int cookies = getCookies(s, t);
	    double areaP = area/n/n;
	    double cookieP = cookies/m;
	    ans = max(ans, cookieP-areaP);
	};

	for(int i = 0; i < m; i++) {
	    cin >> p[i].x >> p[i].y;
	    pd[i] = PD(p[i].x, p[i].y);
	}


	for(int pivot = 0; pivot < m; pivot++) {
	    vector<pair<PL, int>> pts;
	    PL me = p[pivot];
	    int active = 1;
	    for(int i = 0; i < m; i++) {
	        if(i == pivot)
	            continue;
	        PL them = p[i]-me;
	        if(them.half())
	            active++;
	        pts.pb({them, 1});
	        pts.pb({them*-1, -1});
	    }
	    pts.pb({PL(0, 0)-me, 0});
	    pts.pb({PL(n, 0)-me, 0});
	    pts.pb({PL(n, n)-me, 0});
	    pts.pb({PL(0, n)-me, 0});
	    pts.pb({me-PL(0, 0), 0});
	    pts.pb({me-PL(n, 0), 0});
	    pts.pb({me-PL(n, n), 0});
	    pts.pb({me-PL(0, n), 0});
	    angleSort(pts);
	    for(auto [t, delta] : pts) {
	        active += delta;
	        double area = getArea(PD(me.x, me.y), PD(me.x+t.x, me.y+t.y));
	        double areaP = area/n/n;
	        double cookieP = (double)active/m;
	        ans = max(ans, cookieP-areaP);
	    }
	}
	
	for(int pivot = 0; pivot < m; pivot++) {
	    PD me = pd[pivot];
	    vector<double> xs{me.x, n-me.x};
	    vector<double> ys{me.y, n-me.y};
	    for(auto x : xs) {
	        for(auto y : ys) {
	            double tanTheta = (double)x/y;
                double dx = y*tanTheta;
                double dy = x/tanTheta;
                check(me, me+PD(dx, dy));
                check(me, me+PD(-dx, dy));
                check(me, me+PD(dx, -dy));
                check(me, me+PD(-dx, -dy));
                check(me+PD(dx, dy), me);
                check(me+PD(-dx, dy), me);
                check(me+PD(dx, -dy), me);
                check(me+PD(-dx, -dy), me);
	        }
	    }
	}
	
	cout << fixed << setprecision(20);
	cout << ans << "\n";
	
}