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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    ll s;
	    cin >> n >> s;
	    int ans = 0;
	    for(int i = 0; i < n; i++) {
	        ll dx, dy, x, y;
	        cin >> dx >> dy >> x >> y;
	        if(x==y && dx==dy)
	            ans++;
	        else if(x+y==s && dx!=dy)
	            ans++;
	    }
	    cout << ans << "\n";
	}
}