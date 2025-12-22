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
	int t;
	cin >> t;
	while(t-->0) {
	    int n, k;
	    cin >> n >> k;
	    vector<int> r(n);
	    vector<int> l(n);
	    vector<ll> m(n);
	    vector<ll> m2(n);
	    for(int i = 0; i < n; i++) {
	        cin >> l[i];
	    }
	    for(int i = 0; i < n; i++) {
	        cin >> r[i];
	        m[i] = max(l[i], r[i]);
	        m2[i] = min(l[i], r[i]);
	    }
	    ll res = accumulate(all(m), 0LL);
	    sort(all(m2));
	    reverse(all(m2));
	    for(int i = 0; i < k-1; i++)
	        res += m2[i];
	    cout << res+1 << "\n";
	}
}