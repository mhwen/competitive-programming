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
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	ll ans = (ll)n*(n+1)/2;
	
	auto update = [&](int i, int v) {
	    if(i > 0) {
	        ll right = n-i;
	        ll left = i;
	        if(a[i] != a[i-1] && v == a[i-1])
	            ans -= right*left;
	        else if(a[i] == a[i-1] && v != a[i-1])
	            ans += right*left;
	    }
	    if(i < n-1) {
	        ll left = i+1;
	        ll right = n-i-1;
	        if(a[i] != a[i+1] && v == a[i+1])
	            ans -= left*right;
	        else if(a[i] == a[i+1] && v != a[i+1])
	            ans += left*right;
	    }
	    a[i] = v;
	};
	
	for(int i = 0; i < n; i++) {
        int v;
        cin >> v;
        update(i, v);   
	}
	while(m-->0) {
	    int i, x;
	    cin >> i >> x;
	    i--;
	    update(i, x);
	    cout << ans << "\n";
	}
	
}