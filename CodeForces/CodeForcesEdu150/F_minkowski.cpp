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
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator<(P p) const {
		return half() == p.half() ? cross(p) > 0 : half() < p.half();
	}
	bool half() const { return y < 0 || (y == 0 && x < 0); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T dist2() const { return x*x + y*y; }
};

typedef Point<__int128> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	P p(0, 0);
	vector<P> slopes;
	for(int i = 0; i < n; i++) {
		ll a, b, c, d;
		cin >> a >> b >> c >> d;
		ll x = b-a;
		ll y = d-c;
		if(x == 0 && y == 0)
			continue;
		if(y < 0 || (y == 0 && x < 0))
			p = p+P(x, y);
		slopes.push_back(P(x, y));
		slopes.push_back(P(-x, -y));
	}
	sort(all(slopes));
	__int128 best = p.dist2();
	for(auto s : slopes) {
		p = p+s;
		best = max(best, p.dist2());
	}
	cout << setprecision(25) << (ld)best << "\n";
}