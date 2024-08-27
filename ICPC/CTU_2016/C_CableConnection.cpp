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
	explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
	bool operator <(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator ==(P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

typedef Point<ld> P;
vector<P> convexHull(vector<P> pts) {
	if(sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for(int it = 2; it--; s = --t, reverse(all(pts)))
		for(P p : pts) {
			while(t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

constexpr ld INF = 1e15;
constexpr ld EPS = 1e-6;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n) {
		
		vector<P> points(n);
		int maxX = 0, maxY = 0;
		for(int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			points[i] = P(x, y);
			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}
		P Y = P(0, maxY+EPS);
		P X = P(maxX+EPS, 0);
		points.push_back(Y);
		points.push_back(X);
		auto hull = convexHull(points);
		reverse(all(hull));
		n = sz(hull);
		
		int start = -1;
		for(int i = 0; i < n; i++) {
			hull.push_back(hull[i]);
			if(hull[i] == Y)
				start = i;
		}
		int end = -1;
		for(int i = start; i < sz(hull); i++) {
			if(hull[i] == X) {
				end = i;
				break;
			}
		}
		ld best = INF;
		
		for(int i = start+1; i < end; i++) {
			P prev = hull[i-1];
			P curr = hull[i];
			P next = hull[i+1];
			ld prevSlope = (curr.y-prev.y)/(curr.x-prev.x);
			ld prevB = curr.y-prevSlope*curr.x;
			ld nextSlope = (next.y-curr.y)/(next.x-curr.x);
			ld nextB = curr.y-nextSlope*curr.x;
			ld prevY = prevB;
			ld prevX = -prevB/prevSlope;
			ld nextY = nextB;
			ld nextX = -nextB/nextSlope;
			
			best = min(best, prevY*prevY+prevX*prevX);
			best = min(best, nextY*nextY+nextX*nextX);
			
			auto eval = [&](ld z) {
				ld a = curr.x+z;
				ld b = curr.y+curr.x*curr.y/z;
				return a*a+b*b;
			};
			
			ld left = nextX-curr.x;
			ld right = prevX-curr.x;
			while(right-left > EPS) {
				ld diff = (right-left)/3;
				ld lp = left+diff;
				ld rp = left+diff*2;
				if(eval(lp) < eval(rp))
					right = rp;
				else
					left = lp;
			}
			best = min(best, eval((left+right)/2));
		}
		
		cout << fixed << setprecision(20) << sqrt(best) << "\n";
	}
}