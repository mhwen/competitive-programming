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
	bool operator<(P p) const { 
		if(half() != p.half())
			return half() < p.half();
		return cross(p) > 0;
	}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	int half() const { return y < 0 || (y == 0 && x < 0); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}
};

typedef Point<ll> P;

ll read() {
	ld val;
	cin >> val;
	return (ll)round(val*1e6);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;
	vector<P> chocs(n);
	for(int i = 0; i < n; i++) {
		ll x = read();
		ll y = read();
		chocs[i] = P(x, y);
	}
	vector<P> straws(m);
	for(int i = 0; i < m; i++) {
		ll x = read();
		ll y = read();
		straws[i] = P(x, y);
	}
	
	auto solve = [&](int id) {
		P pivot = straws[id];
		vector<pair<P, int>> events;
		for(auto p : chocs)
			events.push_back({p-pivot, 0});
		for(int i = 0; i < m; i++)
			if(i != id)
				events.push_back({straws[i]-pivot, 1});
		sort(all(events));

		vector<int> counts(2);
		int best = 0;
		int right = 0;
		for(int left = 0; left < sz(events); left++) {
			auto leftPoint = events[left].first;
			while(right < left+sz(events)) {
				auto rightPoint = events[right%sz(events)].first;
				ll cross = leftPoint.cross(rightPoint);
				if(cross > 0 || (cross == 0 && leftPoint.dot(rightPoint) > 0)) {
					counts[events[right%sz(events)].second]++;
					right++;
				}
				else
					break;
			}
			if(counts[1] == 0)
				best = max(best, counts[0]);
			counts[events[left].second]--;
		}
		return best;
	};
	
	int ans = 0;
	for(int i = 0; i < m; i++)
		ans = max(ans, solve(i));
	
	cout << ans << "\n";

	
}