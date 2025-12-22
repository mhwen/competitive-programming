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
		ll x, m;
		cin >> x >> m;
		ll ans = 0;
		for(int y = 1; y <= min(4*x, m); y++) {
			if(y == x)
				continue;
			ll xy = x^y;
			if(y%xy==0 || x%xy == 0)
				ans++;
		}
		cout << ans << "\n";
	}
}