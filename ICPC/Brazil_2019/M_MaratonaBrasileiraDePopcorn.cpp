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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, c, t;
	cin >> n >> c >> t;
	vector<ll> p(n);
	for(int i = 0; i < n; i++) {
		cin >> p[i];
	}
	
	auto check = [&](ll time) {
		int guy = 1;
		ll used = 0;
		for(ll eat : p) {
			if(used+eat <= time*t)
				used += eat;
			else {
				if(eat > time*t)
					return false;
				used = eat;
				guy++;
				if(guy > c)
					return false;
			}
		}
		return true;
	};
	
	ll l = 0, r = 2e9;
	while(l <= r) {
		ll mid = l+(r-l)/2;
		if(check(mid))
			r = mid-1;
		else
			l = mid+1;
	}
	cout << l << "\n";
}