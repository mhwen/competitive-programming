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
	ll x, y;
	P(ll _x=0, ll _y=0): x(_x), y(_y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	ll cross(P p) const { return x*p.y - y*p.x; }
	ll cross(P a, P b) const { return (a-*this).cross(b-*this); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef map<tuple<ll, ll, ll>, map<P, int>> cloud;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	auto line = [&](P p, P q) {
		ll x1 = p.x;
		ll y1 = p.y;
		ll x2 = q.x;
		ll y2 = q.y;
		ll A = y1-y2;
		ll B = x2-x1;
		ll C = x1*y2-y1*x2;
		ll g = gcd(A, gcd(B, C));
		A/=g; B/=g; C/=g;
		if(A < 0 || (A == 0 && B < 0)) {
			A = -A; B = -B; C = -C;
		}
		return make_tuple(A, B, C);
	};
	
	auto add = [&](P a, P b, cloud& s) {
		auto l = line(a, b);
		s[l][a]++;
		s[l][b]--;
	};
	
	cloud s1;
	cloud s2;
	
	auto readCloud = [&](int N, cloud& s) {
		for(int i = 0; i < N; i++) {
			P a, b, c;
			cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
			if(a.cross(b, c) > 0) {
				swap(b, c);
			}
			add(a, b, s);
			add(b, c, s);
			add(c, a, s);
		}
	};
	int n;
	cin >> n;
	readCloud(n, s1);
	int m;
	cin >> m;
	readCloud(m, s2);
	
	auto process = [](cloud& s) {
		for(auto& [_, b] : s) {
			for(auto it = b.begin(); it != b.end(); ) {
				if(it->second == 0)
					it = b.erase(it);
				else
					it++;
			}	
		}
		for(auto it = s.begin(); it != s.end(); ) {
			if(it->second.empty())
				it = s.erase(it);
			else
				it++;
		}
	};

	process(s1);
	process(s2);
	
	if(s1 == s2)
		cout << "yes\n";
	else
		cout << "no\n";
}