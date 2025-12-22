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
	bool operator<(P p) const { 
	    return half() == p.half() ? cross(p) > 0 : half() < p.half();
	}
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	bool half() const { return y < 0 || (y == 0 && x < 0); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts), [](P a, P b) {
	    return tie(a.x,a.y) < tie(b.x,b.y);
	});
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
ld lineDist(const P& a, const P& b, const P& p) {
	return abs((b-a).cross(p-a)/(b-a).dist());
}

template<class P>
ld lineDist(ld A, ld B, ld C, const P& p) {
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

vector<pair<P, pair<P, P>>> convert(vector<P> hull) {
    vector<pair<P, pair<P, P>>> pts;
    for(int i = 0; i < sz(hull); i++) {
        int j = (i+1)%sz(hull);
        pts.emplace_back(hull[j]-hull[i], pair{hull[i], hull[j]});
    }
    return pts;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<P> points(n);
	for(int i = 0; i < n; i++) {
	    cin >> points[i].x >> points[i].y;
	}
	vector<pair<P, pair<P, P>>> hull = convert(convexHull(points));
	sort(all(hull));
	vector<pair<P, int>> lines;
	
	vector<ll> A(q);
	vector<ll> B(q);
	vector<ll> C(q);

	for(int i = 0; i < q; i++) {
	    cin >> A[i] >> B[i] >> C[i];
	    lines.emplace_back(P(-B[i], A[i]), i);
	}
	
	vector<ld> ans(q);
	auto check = [&]() {
	    sort(all(lines));
    	int pid = 0;
    	for(auto [dir, id] : lines) {
    	    while(pid < sz(hull) && hull[pid].first < dir)
    	        pid++;
    	    P p1 = hull[pid%sz(hull)].second.first;
    	    P p2 = hull[pid%sz(hull)].second.second;
    	    ans[id] = max(ans[id], lineDist(A[id], B[id], C[id], p1));
    	    ans[id] = max(ans[id], lineDist(A[id], B[id], C[id], p2));
    	}
	};
	
	check();
	for(int i = 0; i < sz(lines); i++) {
	    lines[i].first = lines[i].first * -1;
	}
    check();
	
	cout << fixed << setprecision(10);
	for(auto a : ans)
	    cout << a << "\n";
}