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
	explicit Point(T _x, T _y) : x(_x), y(_y) {}
	bool operator<(P p) const {
		return half() == p.half() ? cross(p) > 0 : half() < p.half();
	}
	bool half() const { return y < 0 || (y == 0 && x < 0); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	T dist2() const { return x*x + y*y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << (ll)p.x << "," << (ll)p.y << ")"; }
};

typedef Point<__int128> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<P> p;
	P curr(0, 0);
	for(int i = 0; i < n; i++) {
		ll a, b, c, d;
		cin >> a >> b >> c >> d;
		ll x = b-a;
		ll y = d-c;
		if(x == 0 && y == 0)
			continue;
		p.push_back(P(x, y));
		p.push_back(P(-x, -y));
		if(P(x,y).half())
			curr = curr+P(x,y);
	}
	__int128 best = curr.dist2();
	sort(all(p));
	for(auto pp : p) {
		curr = curr+pp;
		best = max(best, curr.dist2());
	}
	cout << setprecision(25) << (ld)best << "\n";
	
}