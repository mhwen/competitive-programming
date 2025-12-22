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
	ll n, k;
	cin >> n >> k;
	ll curr = 1;
	ll rem = n-1;
	ll ans = 0;
	while(rem > 0 && curr < k) {
		ll add = min(curr, k);
		rem -= add;
		curr += add;
		ans++;
	}
	if(rem > 0)
		ans += (rem+k-1)/k;
	cout << ans << "\n";
}