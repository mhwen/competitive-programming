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
	    int n;
	    cin >> n;
	    int zeros = 0;
	    vector<int> a(n);
	    int firstZ = n;
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        if(a[i] == 0) {
	            zeros++;
	            firstZ = min(firstZ, i);
	        }
	    }
	    int ans = n-zeros;
	    if(zeros > 0) {
	        set<int> seen;
	        for(int i = firstZ; i < n; i++) {
	            seen.insert(a[i]);
	        }
	        int mex = 0;
	        bool good = true;
	        for(int i = firstZ-1; i >= 0; i--) {
	            while(seen.count(mex))
	                mex++;
	            if(a[i] < mex)
	                good = false;
	            seen.insert(a[i]);
	        }
	        if(good)
	            ans++;
	    }
	    cout << ans << "\n";
	}
}