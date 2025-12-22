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
#define rep(i, a, b) for(int i = a; i < (b); i++)
constexpr ll INF = 1e18;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
};

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
bool inPolygon(vector<P>& p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i, 0, n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

typedef Point<ll> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	auto dist = [&](P a, P b) {
		return sqrt((ld)(a-b).dist2());
	};
	cout << fixed << setprecision(20);
	int t;
	cin >> t;
	for(int ca = 1; ca <= t; ca++) {
		int n;
		cin >> n;
		vector<P> p(n);
		for(int i = 0; i < n; i++) {
			ll x, y;
			cin >> x >> y;
			p[i] = P(x, y);
		}
		ll x, y;
		cin >> x >> y;
		P target = P(x, y);
		ld best = INF;
		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				for(int k = j+1; k < n; k++) {
					vector<P> triangle{p[i], p[j], p[k]};
					if(inPolygon(triangle, target)) {
						best = min(best, dist(p[i], p[j])+dist(p[j], p[k])+dist(p[k], p[i]));
					}
				}
				if(onSegment(p[i], p[j], target)) {
					ld neg = INF;
					ld pos = INF;
					for(int k = 0; k < n; k++) {
						if(k == i || k == j)
							continue;
						ll dir = p[i].cross(p[j], p[k]);
						if(dir > 0)
							pos = min(pos, dist(p[i], p[k])+dist(p[j], p[k]));
						if(dir < 0)
							neg = min(neg, dist(p[i], p[k])+dist(p[j], p[k]));
					}
					best = min(best, neg+pos);
				}
			}
		}
		if(best == INF)
			cout << "Case #" << ca << ": IMPOSSIBLE\n";
		else
			cout << "Case #" << ca << ": " << best << "\n";
	}
}