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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<int> b(n);
	vector<int> w(n);
	vector<int> v(n);
	for(int i = 0; i < n; i++)
	    cin >> b[i];
	for(int i = 0; i < n; i++)
	    cin >> w[i];
	for(int i = 0; i < n; i++)
	    cin >> v[i];
	vector<ll> p(1e5+5);
	for(int i = 0; i < n; i++) {
	    int mn = b[i];
	    int mx = k-w[i];
	    if(mn <= mx) {
	        p[mn] += v[i];
	        p[mx+1] -= v[i];
	    }
	}
	ll best = 0;
	for(int i = 1; i < sz(p); i++) {
	    p[i] += p[i-1];
	    best = max(best, p[i]);
	}
	cout << best << "\n";
}