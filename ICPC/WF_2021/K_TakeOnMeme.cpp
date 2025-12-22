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

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	bool operator<(P p) const { return tie(x,y)<tie(p.x,p.y); }
	bool half() const { return y<0 || (y==0 && x<0); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
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

vector<P> minkowski(vector<vector<P>>& hulls) {
	P curr(0, 0);
	vector<P> slopes;
	for(auto& ps : hulls) {
		P lo = ps[0];
		if(sz(ps) > 1) {
			P prev = ps.back();
			for(auto p : ps) {
				slopes.push_back(p-prev);
				if(p.y < lo.y || (p.y==lo.y && p.x<lo.x))
					lo = p;
				prev = p;
			}
		}
		curr = curr+lo;
	}
	if(slopes.empty()) return vector<P>{curr};
	
	sort(all(slopes), [](P a, P b) {
		return a.half()==b.half() ? a.cross(b)>0 : a.half()<b.half();
	});
	vector<P> sum;
	P prev(0, 0);
	for(auto s : slopes) {
		if(!(s.cross(prev)==0 && s.dot(prev)>0))
			sum.push_back(curr);
		curr = curr+s;
		prev = s;
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> con(n);
	vector<vector<P>> sums(n);
	for(int i = 0; i < n; i++) {
		int k;
		cin >> k;
		if(k) {
			for(int j = 0; j < k; j++) {
				int c;
				cin >> c;
				c--;
				con[i].push_back(c);
			}
		}
		else {
			ll x, y;
			cin >> x >> y;
			sums[i].push_back(P(x, y));
		}
	}
	function<void(int)> dfs = [&](int curr) {
		if(con[curr].empty())
			return;
		vector<vector<P>> hulls;
		for(int next : con[curr]) {
			dfs(next);
			hulls.push_back(sums[next]);
		}
		vector<P> possible;
		for(int i = 0; i < sz(hulls); i++) {
			vector<vector<P>> sum;
			for(int j = 0; j < sz(hulls); j++) {
				if(j == i)
					sum.push_back(hulls[j]);
				else {
					vector<P> hull;
					for(auto p : hulls[j])
						hull.push_back(p*-1);
					sum.push_back(hull);
				}
			}
			vector<P> res = minkowski(sum);
			for(auto p : res)
				possible.push_back(p);
		}
		sums[curr] = convexHull(possible);
	};
	dfs(0);
	ll best = 0;
	for(auto p : sums[0])
		best = max(best, p.x*p.x+p.y*p.y);
	cout << best << "\n";
}