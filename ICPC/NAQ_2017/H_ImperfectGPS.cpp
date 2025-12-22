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

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	ld dist() const { return sqrt(dist2()); }
	T dist2() const { return x*x + y*y; }
};

typedef Point<ld> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, T;
	cin >> n >> T;
	
	vector<int> times(n);
	vector<P> pos(n);
	for(int i = 0; i < n; i++) {
		cin >> pos[i].x >> pos[i].y >> times[i];
	}
	vector<P> actual(times.back()+1);
	ld total = 0;
	for(int i = 0; i < n-1; i++) {
		P from = pos[i];
		P to = pos[i+1];
		int delta = times[i+1]-times[i];
		P v = (to-from)/delta;
		total += (to-from).dist();
		for(int t = 0; t < delta; t++) {
			actual[times[i]+t] = from+v*t;
		}
	}
	actual[times.back()] = pos.back();
	
	vector<pair<P, int>> gps;
	for(int i = 0; i < sz(actual); i += T) {
		gps.emplace_back(actual[i], i);
	}
	ld gpsCount = 0;
	gps.emplace_back(pos.back(), times.back());
	for(int i = 0; i < sz(gps)-1; i++) {
		P from = gps[i].first;
		P to = gps[i+1].first;
		gpsCount += (to-from).dist();
	}
	ld diff = total-gpsCount;
	cout << fixed << setprecision(20) << diff/total*100 << "\n";
}