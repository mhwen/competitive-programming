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
	int t;
	cin >> t;
	while(t-->0) {
		int l, r;
		int L, R;
		cin >> l >> r >> L >> R;
		int ml = max(l, L);
		int mr = min(r, R);
		int middle = max(0, mr-ml+1);
		if(middle == 0)
			cout << 1 << "\n";
		else {
			int ans = middle-1;
			if(R > mr || r > mr)
				ans++;
			if(L < ml || l < ml)
				ans++;
			cout << ans << "\n";
		}
	}
}