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
typedef int ll;
typedef double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x,y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}
};

typedef Point<ll> P;
vector<P> convexHull (vector<P>& pts) {
	if(sz(pts) <= 1) return pts;
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for( int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	reverse(all(pts));
	return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

ll hullDiameter(vector<P>& S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ll, array<P, 2>> res({0, {S[0], S[0]}});
	rep(i,0,j)
		for (;; j = (j+1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.first;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<P> points(n);
	vector<vector<P>> sorted(n);
	for(int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		points[i] = P(x, y);
		for(int j = 0; j < n; j++) {
			if(j != i)
				sorted[j].push_back(points[i]);
		}
	}
	for(int i = 0; i < n; i++) {
		sort(all(sorted[i]));
	}
	
	auto checkPoint = [&](int id, ll dist) {
		vector<P> others;
		for(int i = 0; i < sz(sorted[id]); i++) {
			if((points[id]-sorted[id][i]).dist2() >= dist)
				others.push_back(sorted[id][i]);
		}
		if(sz(others) <= 1)
			return (ll)0;
		auto hull = convexHull(others);
		ll res = hullDiameter(hull);
		return res;
	};

	auto check = [&](ll dist) {
		for(int i = 0; i < n; i++) {
			if(checkPoint(i, dist) >= dist)
				return true;
		}
		return false;
	};	
	
	vector<ll> dists;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			dists.push_back((points[i]-points[j]).dist2());
		}
	}
	sort(dists.begin(), dists.end());
	int left = 0, right = sz(dists)-1;
	while(left <= right) {
		int mid = (left+right)/2;
		if(check(dists[mid]))
			left = mid+1;
		else
			right = mid-1;
	}
	cout << fixed << setprecision(20) << sqrt(dists[right])/2 << "\n";
	
}