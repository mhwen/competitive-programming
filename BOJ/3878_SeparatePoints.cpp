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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x, p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}
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
			h[t++]= p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

bool inHull(const vector<P>& l, P p, bool strict = false) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r) return false;
	while(abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

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

    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);

    vector<P> result;
    int i = 0, j = 0;
    while (i < sz(p) - 2 || j < sz(q) - 2) {
        result.push_back(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if (cross >= 0 && i < sz(p) - 2) ++i;
        if (cross <= 0 && j < sz(q) - 2) ++j;
    }
    return result;
}

bool hullIntersect(vector<P> a, vector<P> b) {

	for(int i = 0; i < sz(b); i++) {
		b[i] = b[i]*-1;
	}
	auto sum = minkowski(a, b);
	return inHull(sum, P(0, 0));
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<P> black(n);
		vector<P> white(m);
		for(int i = 0; i < sz(black); i++) {
			int x, y;
			cin >> x >> y;
			black[i] = P(x, y);
		}
		for(int i = 0; i < sz(white); i++) {
			int x, y;
			cin >> x >> y;
			white[i] = P(x, y);
		}
		vector<P> bHull = convexHull(black);
		vector<P> wHull = convexHull(white);
		if(hullIntersect(bHull, wHull))
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}