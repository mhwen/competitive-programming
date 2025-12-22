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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	bool found = false;
	ld m = 1e9;
	for(int i = 0; i < n; i++) {
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		// ld A = y1-y2;
		ld B = x2-x1;
		ld C = x1*y2-y1*x2;
		//Ax + By + C = 0
		//y = (-C-Ax)/B
		ld y = -C/B;
		if(y > 0 && min(x1, x2) <= 0 && max(x1, x2) >= 0) {
			if(found)
				m = min(m, y);
			else
				m = y;
			found = true;
		}
	}
	if(found)
		cout << fixed << setprecision(20) << m << "\n";
	else
		cout << -1 << "\n";
}