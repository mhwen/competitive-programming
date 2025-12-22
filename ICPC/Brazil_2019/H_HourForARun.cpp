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
	ll v, n;
	cin >> v >> n;
	ll tot = v*n;
	ll needed = 1;
	vector<ll> ans;
	for(ll val = 1; val <= tot && needed < 10; val++) {
		while(needed < 10 && tot*needed <= val*10) {
			ans.push_back(val);
			needed++;
		}
	}
	for(ll l : ans)
		cout << l << " ";
	cout << "\n";
}