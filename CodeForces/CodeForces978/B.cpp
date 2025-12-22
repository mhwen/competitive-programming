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
		int n, x;
		cin >> n >> x;
		vector<ll> cars(n);
		for(ll& l : cars)
			cin >> l;
		ll sum = accumulate(all(cars), 0LL);
		ll mx = *max_element(all(cars));
		cout << max(mx, (sum+x-1)/x) << "\n";
	}
}