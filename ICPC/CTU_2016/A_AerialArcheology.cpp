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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y);}
	P operator-(P p) const { return P(x-p.x, y-p.y);}
	P operator*(T d) const { return P(x*d, y*d); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}
};

typedef Point<ll> P;

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

P normalize(P p) {
	ll div = gcd(abs(p.x), abs(p.y));
	return P(p.x/div, p.y/div);
}

bool up(P p) {
	return p.y > 0 or (p.y == 0 and p.x >= 0);
}

int main() {
	
	auto cmp = [](P a, P b) {
		return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n) {
		vector<vector<P>> p(n+1);
		for(int i = 1; i <= n; i++) {
			int len;
			cin >> len;
			for(int j = 0; j < len; j++) {
				int x, y;
				cin >> x >> y;
				p[i].push_back(P(x, y));
			}
			p[i] = convexHull(p[i]);
		}
		
		auto check = [&](P pivot) {
			map<P, vector<int>> events;
			vector<int> caps(n+1);
			for(int i = 1; i <= n; i++) {
				int mySz = sz(p[i]);
				caps[i] = mySz;
				for(int j = 0; j < mySz; j++) {
					P point = p[i][j];
					P enter, exit;
					if(point == pivot) {
						P prev = p[i][(j-1+mySz)%mySz];
						P next = p[i][(j+1)%mySz];
						enter = normalize(prev-pivot)*-1;
						exit = normalize(next-pivot)*-1;
					}
					else {
						enter = normalize(point-pivot);
						exit = enter*-1;
					}
					events[enter].push_back(i);
					events[exit].push_back(-i);
				}
			}
			vector<P> order;
			for(auto [point, event] : events) {
				order.push_back(point);
			}
			sort(all(order), cmp);
			vector<int> counts(n+1);
			int hit = 0;
			for(int i = 1; i < sz(order); i++) {
				if(order[i] == order[0]*-1) {
					for(int j = i; j < sz(order); j++) {
						for(auto e : events[order[j]]) {
							if(e > 0)
								counts[e]++;
						}
					}
					break;
				}
			}
			for(int i = 1; i <= n; i++) {
				if(counts[i] > 0 && counts[i] < caps[i])
					hit++;
			}
			int best = hit;
			for(int i = 0; i < sz(order); i++) {
				for(int e : events[order[i]]) {
					if(e > 0) {
						counts[e]++;
						if(counts[e] == 1)
							hit++;
						if(counts[e] == caps[e])
							hit--;
					}
					else {
						e = abs(e);
						counts[e]--;
						if(counts[e] == 0)
							hit--;
						if(counts[e] == caps[e]-1)
							hit++;
					}
				}
				best = max(best, hit);
			}
			return best;
		};
		
		int best = 0;
		for(int i = 1; i <= n; i++) {
			for(Point point : p[i])
				best = max(best, check(point));
		}
		cout << best << "\n";
	}
}