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

//10:43
//11:20

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
	double dist() const { return sqrt((double)dist2()); }
	P unit() const { return *this/dist(); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")"; 
	}
};

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if(h2 < 0) return {};
	if(h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

typedef Point<double> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<P> centers(n+q+1);
	vector<double> radii(n+q+1);
	centers[0] = P(0, 0);
	radii[0] = 1e9;
	//1 = add, 2 = delete
	vector<pair<pair<int, int>, int>> events;
	for(int i = 1; i <= n+q; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		centers[i] = P(x, y);
		radii[i] = r;
		events.push_back({{x-r, 1}, i});
		events.push_back({{x+r, 2}, i});
	}
	sort(events.begin(), events.end());
	
	int currX = -1e9;
	
	auto getY = [&](int id) {
		int I = abs(id);
		auto points = circleLine(centers[I], radii[I], P(currX, 0), P(currX, 1));
		//lower arc
		if(id < 0)
			return points.front().y;
		//upper arc
		else
			return points.back().y;
	};
	
	auto cmp = [&](int a, int b) {
		if(abs(a) == abs(b))
			return a < b;
		double aY = getY(a);
		double bY = getY(b);
		return aY < bY;
	};
	
	set<int, decltype(cmp)> sweep(cmp);
	sweep.insert(0);
	
	vector<int> parent(n+q+1);
	vector<vector<int>> con(n+q+1);
	for(auto e : events) {
		currX = e.first.first;
		int type = e.first.second;
		int id = e.second;
		if(type == 1) {
			int above = *sweep.upper_bound(id);
			//sibling
			if(above < 0) {
				int par = parent[abs(above)];
				parent[id] = par;
				con[par].push_back(id);
			}
			//parent
			else {
				parent[id] = above;
				con[above].push_back(id);
			}
			sweep.insert(id);
			sweep.insert(-id);
		}
		else {
			sweep.erase(id);
			sweep.erase(-id);
		}
	}
	
	vector<vector<int>> dp(2, vector<int>(n+q+1));
	
	function<void(int)> dfs = [&](int curr) {
		for(int next : con[curr]) {
			dfs(next);
		}
		//real node
		if(curr <= n)
			dp[1][curr] = 1;
		
		for(int next : con[curr]) {
			dp[0][curr] += max(dp[0][next], dp[1][next]);
			if(next <= n)
				dp[1][curr] += dp[0][next];
			else
				dp[1][curr] += dp[1][next];
		}
	};
	
	dfs(0);
	
	for(int i = 1; i <= q; i++)
		cout << max(dp[0][n+i], dp[1][n+i]+1) << "\n";
}