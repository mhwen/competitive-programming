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
	ll d, x;
	cin >> n >> d >> x;
	vector<ll> k(n);
	vector<ll> c(n);
	for(ll& l : k)
		cin >> l;
	for(ll& l : c)
		cin >> l;
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b){
		return c[a] > c[b];
	});
	ll ans = 0;
	ll rem = d*x;
	for(int i : order) {
		ll val = c[i];
		ll amt = min(d, k[i]);
		ll take = min(rem, amt);
		ans += val*take;
		rem -= take;
	}
	cout << ans << "\n";
	
}