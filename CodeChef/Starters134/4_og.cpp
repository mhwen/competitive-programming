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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n;
		cin >> n;
		ll ans = 0;
		for(ll dig = 1; dig <= 9; dig++) {
			ans += (n+9-dig)/9*dig;
		}
		cout << ans << "\n";
	}
}