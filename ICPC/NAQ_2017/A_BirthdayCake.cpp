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
	T dist2() const { return x*x + y*y; }
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if(d == 0)
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
typedef Point<ld> P;

template<class T>
T sign(P p, T a, T b, T c) {
	return p.x*a+p.y*b+c;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, r;
	cin >> n >> m >> r;
	vector<P> candles(n);
	for(int i = 0; i < n; i++) {
		cin >> candles[i].x >> candles[i].y;
	}
	vector<pair<P, P>> lines(m);
	vector<ld> A(m);
	vector<ld> B(m);
	vector<ld> C(m);
	for(int i = 0; i < m; i++) {
		ld a, b, c;
		cin >> a >> b >> c;
		A[i] = a;
		B[i] = b;
		C[i] = c;
		if(b!=0) {
			lines[i].first = P(1, (-c-a)/b);
			lines[i].second = P(-1, (-c+a)/b);
		}
		else {
			lines[i].first = P((-c-b)/a, 1);
			lines[i].second = P((-c+b)/a, -1);
		}
	}
	bool bad = false;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			int iCount = 0;
			for(int h = 0; h < m; h++) {
				ld s1 = sign(candles[i], A[h], B[h], C[h]);
				ld s2 = sign(candles[j], A[h], B[h], C[h]);
				if(s1*s2 < 0)
					iCount++;
			}
			if(iCount == 0)
				bad = true;
		}
	}
	int components = m+1;
	for(int i = 0; i < m; i++) {
		for(int j = i+1; j < m; j++) {
			auto inter = lineInter(lines[i].first, lines[i].second, lines[j].first, lines[j].second);
			if(inter.first == 1) {
				auto d = inter.second.dist2();
				if(d < r*r)
					components++;
			}
		}
	}
	if(components != n)
		bad = true;
	if(bad)
		cout << "no\n";
	else
		cout << "yes\n";
}