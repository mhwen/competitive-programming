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
	ll best = 0;
	for(int i = 0; i <= k; i++) {
	    int beak = i;
	    int wing = k-beak;
	    ll tot = 0;
	    for(int j = 0; j < n; j++) {
	        if(beak >= b[j] && wing >= w[j])
	            tot += v[j];
	    }
	    best = max(best, tot);
	}
	cout << best << "\n";
}