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
	int t;
	cin >> t;
	while(t-->0) {
		ll l, r, G;
		cin >> l >> r >> G;
		ll lo = (l+G-1)/G;
		ll hi = r/G;
		ll L = -1;
		ll R = -1;
		bool found = false;
		for(ll len = 0; len <= hi-lo; len++) {
			for(ll i = 0; i <= len; i++) {
				if(gcd(lo+i, hi-(len-i)) == 1) {
					found = true;
					L = (lo+i)*G;
					R = (hi-(len-i))*G;
					break;
				}
			}
			if(found)
				break;
		}
		cout << L << " " << R << "\n";
	}
}