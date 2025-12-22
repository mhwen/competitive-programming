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

constexpr ld PI = acos(-1);
constexpr ld EPS = 1e-9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, r;
	cin >> n >> r;
	ld totArea = PI*r*r;
	auto compute = [&](ld d) {
		assert(0 <= d && d <= r);
		ld angle = acos(d/r);
		ld chordLen = sqrt(r*r-d*d);
		ld sector = angle*r*r;
		ld triangle = chordLen*d;
		ld res = (sector-triangle)/totArea;
		assert(res <= 0.5+EPS);
		return res;
	};
	
	ld small = 0;
	for(int i = 1; i <= n; i++) {
		int A, B, C;
		cin >> A >> B >> C;
		ld d = abs(C)/sqrt(A*A+B*B);
		ld area = compute(d);
		small = max(small, area);
	}
	
	cout << fixed << setprecision(10) << small << " " << 1-small << "\n";
}