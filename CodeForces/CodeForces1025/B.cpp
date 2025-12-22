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
#define pb push_back

ll solve(ll n, ll m) {
    ll ans = 1;
    while(n > 1) {
        ans++;
        n = (n+1)/2;
    }
    while(m > 1) {
        ans++;
        m = (m+1)/2;
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    ll n, m, a, b;
	    cin >> n >> m >> a >> b;
	    ll ncut = min(a, n-a+1);
	    ll mcut = min(b, m-b+1);
	    cout << min(solve(n, mcut), solve(ncut, m)) << "\n";
	}
}