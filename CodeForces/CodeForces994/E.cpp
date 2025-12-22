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

constexpr int QMAX = 33;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int used = 0;
	auto query = [&](ll l, ll r) {
		cout << "? " << l+1 << " " << r+1 << endl;
		int res;
		used++;
		cin >> res;
		return res;
	};
	
	int t;
	cin >> t;
	while(t-->0) {
		used = 0;
		ll n;
		cin >> n;
		int mask = 0;
		mask |= 4*query(0, n/4-1);
		mask |= 2*query(n/4, n/2-1);
		mask |= 1*query(n/2, 3*n/4-1);
		ll l = 0, r = n-1;
		int pos = 0;
		//truth
		if(mask == 0b000) {
			pos = 3;
			l = n/4+1;
		}
		if(mask == 0b100) {
			pos = 0;
			l = n/4+1;
		}
		if(mask == 0b010) {
			pos = 1;
			l = n/4+1;
		}
		if(mask == 0b001) {
			pos = 2;
			l = n/4+1;
		}
		//lie
		if(mask == 0b111) {
			pos = 3;
			r = n/4;
		}
		if(mask == 0b011) {
			pos = 0;
			r = n/4;
		}
		if(mask == 0b101) {
			pos = 1;
			r = n/4;
		}
		if(mask == 0b110) {
			pos = 2;
			r = n/4;
		}
		bool inLeft = pos < 2;
		auto truth = [&](ll m) {
			if(m >= n/2) {
				if(inLeft)
					return query(0, m-1) == 1;
				else
					return query(n-m, n-1) == 1;
			}
			else {
				if(!inLeft)
					return query(0, m-1) == 0;
				else
					return query(n-m, n-1) == 0;
			}
		};
		
		while(l < r) {
			ll mid = (l+r)/2;
			if(truth(mid))
				l = mid+1;
			else
				r = mid;
			if(used > QMAX)
				return -1;
		}
		assert(l == r);
		cout << "! " << l << endl;
	}
}