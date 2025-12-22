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

typedef Point<ll> P;
vector<P> minkowski(vector<vector<P>>& hulls) {
	P curr(0, 0);
	vector<P> slopes;
	for(auto& ps : hulls) {
		P lo = ps[0];
		for(int i = 0; i < sz(ps); i++) {
			P p = ps[i];
			P next = ps[(i+1)%sz(ps)];
			slopes.push_back(next-p);
			if(p.y < lo.y || (p.y==lo.y && p.x<lo.x))
				lo = p;
		}
		curr = curr+lo;
	}
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
	int n, m;
	cin >> n >> m;
	vector<ll> a(m);
	vector<ll> b(m);
	ll A = 0, B = 0;
	vector<vector<pair<int, int>>> con(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v >> a[i] >> b[i];
		A += a[i];
		B += b[i];
		u--; v--;
		con[u].emplace_back(v, i);
		con[v].emplace_back(u, i);
	}
	
	stack<pair<int, int>> s;
	vector<vector<P>> hulls;
	
	auto addCycle = [&](int head) {
		stack<pair<int, int>> hold;
		vector<P> hull;
		auto process = [&]() {
			int id = s.top().second;
			hold.push(s.top());
			hull.push_back(P(a[id], b[id]));
			s.pop();
		};
		while(s.top().first != head)
			process();
		process();
		while(!hold.empty()) {
			s.push(hold.top());
			hold.pop();
		}
		hulls.push_back(convexHull(hull));
	};
	
	vector<int> vis(n);
	function<void(int, int)> dfs = [&](int curr, int prev) {
		vis[curr] = 1;
		for(auto [next, id] : con[curr]) {
			if(next == prev || vis[next] == 2)
				continue;
			s.push({curr, id});
			if(vis[next] == 1)
				addCycle(next);
			else
				dfs(next, curr);
			s.pop();
		}
		vis[curr] = 2;
	};
	dfs(0, -1);
	auto sum = minkowski(hulls);
	ll best = A*B;
	for(auto h : sum)
		best = min(best, (A-h.x)*(B-h.y));
	cout << best << "\n";
	
}