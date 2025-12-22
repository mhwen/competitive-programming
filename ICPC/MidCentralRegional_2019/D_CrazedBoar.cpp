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
typedef pair<int, int> pii;
typedef vector<int> vi;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

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
		double a = atan2(y, x);
		if(a < 0)
			a += 2*PI;
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

template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
	P d = c2 - c1;
	double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (double sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.pb({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}

typedef Point<double> P;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
		   p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<P> trees(n);
	vector<double> r(n);
	for(int i = 0; i < n; i++)
		cin >> trees[i].x >> trees[i].y >> r[i];
	double b, d;
	cin >> b >> d;
	
	vector<pair<double, int>> events;
	int cnt = 0;
	for(int i = 0; i < n; i++) {
		if(trees[i].dist2() >= (r[i]+b+d)*(r[i]+b+d))
			continue;
		auto t = tangents(P(0, 0), -b, trees[i], r[i]);
		assert(sz(t) == 2);
		double dist = (t[0].second-t[0].first).dist();
		if(dist <= d) {
			double enter = (t[0].second-t[0].first).angle();
			double exit = (t[1].second-t[1].first).angle();
			if(exit < enter)
				cnt++;
			events.emplace_back(enter, 1);
			events.emplace_back(exit, -1);
		}
		else {
			pair<P, P> out;
			assert(circleInter(trees[i], P(0, 0), r[i]+b, d, &out));
			double enter = out.first.angle();
			double exit = out.second.angle();
			if(exit < enter)
				cnt++;
			events.emplace_back(enter, 1);
			events.emplace_back(exit, -1);
		}
	}
	
	sort(all(events));
	double prev = 0;
	double prop = 0;
	for(auto [angle, x] : events) {
		if(cnt == 0)
			prop += angle-prev;
		cnt += x;
		prev = angle;
	}
	if(cnt == 0)
		prop += 2*PI-prev;
	cout << fixed << setprecision(20) << prop/2/PI << "\n";
	
}