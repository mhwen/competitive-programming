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
typedef double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
	bool operator<(P p) const { return half() == p.half() ? cross(p) > 0 : half() < p.half(); }
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
	ld dist() const { return sqrt((ld)dist2()); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;
bool circleInter(P a,P b,ld r1,ld r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	ld d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
		   p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, r;
	cin >> n >> r;
	vector<P> p(n);
	for(int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	
	auto solve = [&](int id) {
		vector<pair<P, int>> events;
		P base = p[id];
		for(int i = 0; i < n; i++) {
			if(i == id)
				continue;
			pair<P, P> inter;
			if(circleInter(p[i], base, r, r, &inter)) {
				P enter = inter.first;
				P exit = inter.second;
				events.emplace_back(enter-base, -(i+1));
				events.emplace_back(exit-base, i+1);
			}
		}
		sort(all(events));
		int best = 0;
		vector<bool> in(n+1);
        int cnt = 0;
		for(int i = 0; i < 2*sz(events); i++) {
			auto [_, e] = events[i%sz(events)];
			if(e < 0) {
                assert(!in[abs(e)]);
				in[abs(e)] = true;
                cnt++;
            }
			else {
				if(in[e]) {
					in[e] = false;
                    cnt--;
                }
			}
			best = max(best, cnt);
		}
		return best;
	};
	
	int ans = 0;
	for(int i = 0; i < n; i++)
		ans = max(ans, solve(i));
	cout << ans+1 << "\n";
	
}