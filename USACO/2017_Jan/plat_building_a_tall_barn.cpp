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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("tallbarn.in");
	ofstream cout("tallbarn.out");
	int n;
	ll k;
	cin >> n >> k;
	vector<ll> a(n);
	for(ll&i : a)
		cin >> i;
		
	auto check = [&](ld time) {
		ld total = 0;
		ll guys = 0; 
		for(ll& i : a) {
			ld val = i/time;
			ll needed = (ll)floor(sqrt(val));
			while(needed*needed-needed < val)
				needed++;
			needed--;
			guys += needed;
			total += (ld)i/needed;
		}
		return pair<ld, ll>{total, guys};
	};
		
	ld left = 0, right = 1e12;
	ll best = 1e18;
	for(int i = 0; i < 200; i++) {
		ld mid = (left+right)/2;
		auto res = check(mid);
		if(res.second <= k) {
			right = mid;
			best = min(best, (ll)round(res.first));
		}
		else
			left = mid;
	}
	cout << best << "\n";
}