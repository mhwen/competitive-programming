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

ll n, k;

pair<ll, ll> solve(ll l, ll r) {
	if(r-l+1 < k)
		return pair{0, 0};
	ll m = (l+r)/2;
	if((r-l+1)%2==0) {
		auto val = solve(l, m);
		return pair{val.first*2, val.second*2+val.first*(m-l+1)};
	}
	else {
		auto val = solve(l, m-1);
		return pair{val.first*2+1, val.second*2+val.first*(m-l+1)+m};
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		cin >> n >> k;
		cout << solve(1, n).second << "\n";
	}
}