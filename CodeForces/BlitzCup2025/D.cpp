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
	int n;
	cin >> n;
	vector<ll> a(n);
	vector<ll> b(n);
	ll best = 0;
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	for(int i = 0; i < n; i++) {
	    cin >> b[i];
	    best += a[i]*b[i];
	}
	ll tot = best;
	auto tryEven = [&](int start) {
	    ll amt = tot;
	    for(int i = 0; i < n; i++) {
	        int L = start-i;
	        int R = start+i;
	        if(L < 0 || R >= n)
	            break;
	        amt -= a[L]*b[L];
	        amt -= a[R]*b[R];
	        amt += a[R]*b[L];
	        amt += a[L]*b[R];
	        best = max(best, amt);
	    }
	};
	auto tryOdd = [&](int start) {
	    ll amt = tot;
	    for(int i = 0; i < n; i++) {
	        int L = start-i-1;
	        int R = start+i;
	        if(L < 0 || R >= n)
	            break;
	        amt -= a[L]*b[L];
	        amt -= a[R]*b[R];
	        amt += a[R]*b[L];
	        amt += a[L]*b[R];
	        best = max(best, amt);
	    }
	};
	
	for(int i = 0; i < n; i++) {
	    tryOdd(i);
	    tryEven(i);
	}
	cout << best << "\n";
}