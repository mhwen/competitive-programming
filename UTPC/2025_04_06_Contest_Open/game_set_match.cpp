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
	vector<ll> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	sort(all(a));
	ll ans = 0;
	ll mex = 0;
	ll extra = 0;
	for(int i = 0; i < n; i++) {
	    if(a[i] < mex)
	        extra += a[i];
	    else {
	        ll over = a[i]-mex;
	        ans += mex*over;
	        mex++;
	    }
	}
	ans += extra*mex;
	for(ll i = mex; i > 1; i--) {
	    ans += i+(i-1)*(i-2);
	}
	cout << ans << "\n";
}