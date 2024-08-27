/*
ID: markhwe1
TASK: fence3
LANG: C++17
*/


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
#include <fstream>

using namespace std;
typedef long long ll;
typedef double ld;
#define sz(x) (int)(x).size()

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")"; }
};

typedef Point<ld> P;
ld segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max((ld)0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

int main() {
	
	ofstream cout("fence3.out");
    ifstream cin("fence3.in");
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<pair<P, P>> fences(n);
	for(int i = 0; i < n; i++) {
		cin >> fences[i].first.x >> fences[i].first.y >> fences[i].second.x >> fences[i].second.y;
	}
	ld bestX = -1, bestY = -1, bestDist = 1e9;
	for(ld x = 0; x <= 100; x+=0.1) {
		ld prevDist = 1e9;
		for(ld y = 0; y <= 100; y+=0.1) {
			P p(x, y);
			ld dist = 0;
			for(auto [a, b] : fences)
				dist += segDist(a, b, p);
			if(dist > prevDist)
				break;
			prevDist = dist;
			if(dist < bestDist) {
				bestX = p.x;
				bestY = p.y;
				bestDist = dist;
			}
		}
	}
	cout << fixed << setprecision(1) << bestX << " " << bestY << " " << bestDist << "\n";
}