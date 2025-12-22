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
#define pb push_back

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
	double angle() const { return atan2(y, x); }
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
void anglesort(vector<P> &v, P p=P(0, 0)) {
	sort(all(v), [p](P a, P b) {
		a = a - p, b = b - p;
		return a.half() == b.half() ? a.cross(b) > 0 : a.half() < b.half();
	});
}

typedef Point<ll> P;

constexpr ll MOD = 998244353;

struct mi {
	ll val;
	mi() : mi(0) {}
	mi(ll v) : val(v) {
		val %= MOD;
		if(val < 0)
			val += MOD;
	}
	mi operator+(mi m2) const { return mi(val+m2.val); }
	mi operator-(mi m2) const { return mi(val-m2.val); }
	mi operator*(mi m2) const { return mi(val*m2.val); }
	mi operator/(mi m2) const { return mi(val*m2.inv().val); }
	mi operator+=(mi m2) { return *this = *this+m2; }
	mi operator-=(mi m2) { return *this = *this-m2; }
	mi operator*=(mi m2) { return *this = *this*m2; }
	mi operator/=(mi m2) { return *this = *this/m2; }
	mi pow(ll b) const {
		mi res = 1;
		mi p = *this;
		while(b > 0) {
			if(b & 1) res *= p;
			p *= p;
			b >>= 1;
		}
		return res;
	}
	mi inv() const {
		return pow(MOD-2);
	}
	friend ostream& operator<<(ostream& os, mi m) {
		return os << m.val;
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<P> p(n);
    for(int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    anglesort(p);
    
    vector good(n, vector<bool>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll d1 = p[i].dist2();
            ll d2 = p[j].dist2();
            ll D = (p[i]-p[j]).dist2();
            if(D > d1 && D > d2) {
                good[i][j] = true;
            }
        }
    }
    vector dp(n, vector(n, vector<mi>(10)));
    for(int i = 0; i < n; i++) {
        dp[i][i][1] = 1;
    }
    mi ans = 0;
    for(int start = 0; start < n; start++) {
        for(int last = start; last < n; last++) {
            for(int size = 1; size < 10; size++) {
                if(good[start][last])
                    ans += dp[start][last][size];
                if(dp[start][last][size].val == 0)
                    continue;
                for(int next = last+1; next < n; next++) {
                    if(good[next][last]) {
                        dp[start][next][size+1] += dp[start][last][size];
                    }
                }
            }
        }
    }
    cout << ans+n << "\n";
}