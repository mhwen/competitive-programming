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

ll getSquares(ld r) {
	ll count = 0;
	for(ll i = 1; r*r-i*i > 0; i++) {
		ld height = sqrt(r*r-i*i);
		ll val = (ll)height;
		count += val*2;
	}
	return count*2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll s;
	cin >> s;
	ld left = 0, right = 1e5;
	for(int i = 0; i < 200; i++) {
		ld mid = (left+right)/2;
		if(getSquares(mid) > s)
			right = mid;
		else
			left = mid;
	}
	cout << setprecision(20) << left << "\n";
}