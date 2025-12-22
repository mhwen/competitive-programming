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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

constexpr double PI = acos(-1);

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
	// angle to x-axis in interval [-pi, pi]
	double angle() const { 
		double a = atan2(y,x);
		if(a < 0)
			a+=2*PI;
		return a;
	}
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<double> P;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
		   p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid - per, mid + per};
	return true;
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n) {
		if(n==0)
			break;
		vector<P> c(n);
		vector<double> r(n);
		for(int i = 0; i < n; i++)
			cin >> c[i].x >> c[i].y >> r[i];			
		auto filter = [&]() {
			vector<P> newC;
			vector<double> newR;
			for(int i = 0; i < n; i++) {
				bool good = true;
				for(int j = 0; j < n; j++) {
					if(j == i)
						continue;
					if(r[i]+(c[i]-c[j]).dist() < r[j])
						good = false;
				}
				if(good) {
					newC.push_back(c[i]);
					newR.push_back(r[i]);
				}
			}
			n = sz(newC);
			c = newC;
			r = newR;
		};
		filter();
		vector<vector<pair<double, pair<int, int>>>> events(n);
		vector<P> inters;
		vector<int> start(n);
		
		auto getAngles = [](P C, pair<P, P> p) {
			double a = (p.first-C).angle();
			double b = (p.second-C).angle();
			return pair{a, b};
		};
		int id = 0;
		auto addEvents = [&](int i, pair<double, double> e, int I) {
			if(e.first > e.second)
				start[i]++;
			events[i].emplace_back(e.first, pair{1, I});
			events[i].emplace_back(e.second, pair{-1, I^1});
		};
		
		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				pair<P, P> out;
				if(circleInter(c[i],c[j],r[i],r[j],&out)) {
					auto res = getAngles(c[i],out);
					addEvents(i, res, id);
					res = getAngles(c[j],out);
					swap(res.first, res.second);
					addEvents(j, res, id^1);
					inters.push_back(out.first);
					inters.push_back(out.second);
					id+=2;
				}
			}
		}
		vector<int> next(sz(inters), -1);
		for(int i = 0; i < n; i++) {
			sort(all(events[i]));
			int curr = start[i];
			for(int j = 0; j < sz(events[i]); j++) {
				curr += events[i][j].second.first;
				int Id = events[i][j].second.second;
				int nxtId = events[i][(j+1)%sz(events[i])].second.second;
				assert(curr >= 0);
				if(curr == 0) {
					assert(next[Id] == -1);
					next[Id] = nxtId;
				}
			}
		}
		vector<P> comp;
		vector<bool> vis(sz(inters));
		int ans = 0;
		for(int i = 0; i < sz(vis); i++) {
			if(!vis[i]) {
				comp.clear();
				int curr = i;
				comp.push_back(inters[curr]);
				vis[curr] = true;
				while(next[curr] != i && next[curr] != -1) {
					curr = next[curr];
					comp.push_back(inters[curr]);
					vis[curr] = true;
				}
				if(polygonArea2(comp) < 0)
					ans++;
			}
		}
		cout << ans+1 << "\n";
	}
}