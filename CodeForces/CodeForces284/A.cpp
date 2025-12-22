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

struct P {
	ll x, y;
	P(ll _x=0, ll _y=0) : x(_x), y(_y) {}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	P a, b;
	cin >> a.x >> a.y >> b.x >> b.y;
	auto side = [&](ll A, ll B, ll C, P p) {
		return A*p.x + B*p.y + C;
	};
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 0; i < n; i++) {
		ll A, B, C;
		cin >> A >> B >> C;
		ll s = side(A, B, C, a);
		ll t = side(A, B, C, b);
		if((s < 0)^(t < 0))
			ans++;
	}
	cout << ans << "\n";
	
}