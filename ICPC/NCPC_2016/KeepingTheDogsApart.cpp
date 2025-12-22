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

struct P {
	ld x, y;
	P() : x(0), y(0) {}
	P(ld _x, ld _y) : x(_x), y(_y) {}
	P operator+(P p) { return P(x+p.x, y+p.y); }
	P operator-(P p) { return P(x-p.x, y-p.y); }
	P operator*(ld d) { return P(x*d, y*d); }
	ld dist2() { return x*x+y*y; }
	ld dist() { return sqrt(dist2()); }
};

ld gss(ld a, ld b, ld (*f)(ld)) {
	ld r = (sqrt(5)-1)/2, eps = 1e-15;
	ld x1 = b - r*(b-a), x2 = a + r*(b-a);
	ld f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { //change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return a;
}

P a, b, c, d;

ld check(ld t) {
	P A = a+(b-a)*t;
	P B = c+(d-c)*t;
	return (A-B).dist2();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<P> dog1(n);
	for(int i = 0; i < n; i++)
		cin >> dog1[i].x >> dog1[i].y;
	int m;
	cin >> m;
	vector<P> dog2(m);
	for(int i = 0; i < m; i++)
		cin >> dog2[i].x >> dog2[i].y;
	ld best = (dog1[0]-dog2[0]).dist();
	a = dog1[0];
	c = dog2[0];
	int d1 = 1, d2 = 1;
	while(d1 < n && d2 < m) {
		P next1 = dog1[d1]-a;
		P next2 = dog2[d2]-c;
		if(next1.dist2() < next2.dist2()) {
			ld ratio = next1.dist()/next2.dist();
			b = dog1[d1++];
			d = c+next2*ratio;
		}
		else {
			ld ratio = next2.dist()/next1.dist();
			b = a+next1*ratio;
			d = dog2[d2++];
		}
		ld T = gss(0, 1, check);
		best = min(best, sqrt(check(T)));
		a = b;
		c = d;
	}
	cout << fixed << setprecision(20) << best << "\n";
}