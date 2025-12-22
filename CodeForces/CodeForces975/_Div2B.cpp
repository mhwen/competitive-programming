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
		int n, q;
		cin >> n >> q;
		vector<int> a(n+1);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		map<ll, ll> cnts;
		for(ll i = 1; i < n; i++) {
			cnts[i*(n-i)] += a[i]-a[i-1]-1;
		}
		for(ll i = 0; i < n; i++) {
			cnts[i*(n-1-i)+n-1]++;
		}
		while(q-->0) {
			ll k;
			cin >> k;
			cout << cnts[k] << " ";
		}
		cout << "\n";
	}
}