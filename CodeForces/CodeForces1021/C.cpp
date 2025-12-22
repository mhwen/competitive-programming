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

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if((a - b) % g != 0)
	    return -1; // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

ll normalize(ll& a, ll& b) {
    ll G = gcd(a, b);
    a /= G;
    b /= G;
    return G;
}

void normalize(ll& a, ll& b, ll& c) {
    ll G = gcd(gcd(a, b), c);
    a /= G;
    b /= G;
    c /= G;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    ll n, x, y, dx, dy;
	    cin >> n >> x >> y >> dx >> dy;
	    ll DX = dx;
	    ll DY = dy;
	    ll scale = normalize(dx, dy);
        ll negX = n-x;
        ll negY = n-y;
	    ll xn = n;
	    ll yn = n;
	    normalize(negX, dx, xn);
	    normalize(negY, dy, yn);
	    ll invDx, invDy, trash;
	    if(euclid(dx, xn, invDx, trash) != 1 || euclid(dy, yn, invDy, trash) != 1) {
	        cout << -1 << "\n";
	        continue;
	    }
	    ll v = crt(negX*invDx%xn, xn, negY*invDy%yn, yn);
	    if(v == -1) {
	        cout << -1 << "\n";
	        continue;
	    }
	    ll endX = v*DX/scale+x;
	    ll endY = v*DY/scale+y;
	    ll ans = endX/n-1 + endY/n-1;
	    ans += (endX+endY+n-1)/(2*n);
	    ans += (abs(endX-endY)+n-1)/(2*n);
	    cout << ans << "\n";
	}
}