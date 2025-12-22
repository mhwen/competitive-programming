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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> x(n);
	vector<ll> h(n);
	for(int i = 0; i < n; i++)
		cin >> x[i] >> h[i];
	ld floor = -5e18;
	
	auto check = [](ll x1, ll y1, ll x2, ll y2) {
		return y2-(ld)(y2-y1)/(x2-x1)*x2;
	};
	
	stack<pair<ll, ll>> s;
	for(int i = 0; i < n; i++) {
		while(sz(s) > 2) {
			auto [x1, h1] = s.top();
			s.pop();
			auto [x2, h2] = s.top();
			s.pop();
			auto a = check(x1, h1, x[i], h[i]);
			auto b = check(x2, h2, x[i], h[i]);
			if(b >= a)
				s.push({x2, h2});
			else {
				s.push({x2, h2});
				s.push({x1, h1});
				break;
			}
		}
		if(!s.empty()) {
			auto [x1, h1] = s.top();
			auto a = check(x1, h1, x[i], h[i]);
			floor = max(floor, a);
		}
		s.push({x[i], h[i]});
	}
	if(floor < 0)
		cout << -1 << "\n";
	else
		cout << fixed << setprecision(20) << floor << "\n";
}