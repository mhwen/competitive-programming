#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld;

ld check(ld a, ld b) {
	ld ab = abs(a-b);
	return min(ab, 360-ab);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		int h, m, s;
		cin >> h >> m >> s;
		ld hProp = ((ld)(60*m+s))/(60*60);
		ld mProp = ((ld)s)/60;
		h %= 12;
		ld hour = (h+hProp)*30;
		ld minute = (m+mProp)*6;
		ld second = s*6;
		// cout << hour << " " << minute << " " << second << endl;
		ld ans = min(check(hour, minute), min(check(hour, second), check(minute, second)));
		cout << setprecision(20) << ans << "\n";
	}
}