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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return abs((double)(b-a).cross(p-a)/(b-a).dist());
}

template<class P>
double lineDist(double A, double B, double C, const P& p) {
    P a, b;
    //Ax + By + C = 0
    //By = -C-Ax
    //Ax = -C-By
    if(B == 0) {
        assert(A != 0);
        a = P(-C/A, 0);
        b = P((-C-B)/A, 1);
    }
    else {
        a = P(0, -C/B);
        b = P(1, (-C-A)/B);
    }
    return lineDist(a, b, p);
}

typedef Point<double> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<P> p(n);
	for(int i = 0; i < n; i++) {
	    int x, y;
	    cin >> x >> y;
	    p[i] = P(x, y);
	}
	cout << fixed << setprecision(10);
	while(q-->0) {
	    int A, B, C;
	    cin >> A >> B >> C;
	    double d = 0;
	    for(auto& pp : p)
	        d = max(d, lineDist(A, B, C, pp));
	    cout << d << "\n";
	}
}