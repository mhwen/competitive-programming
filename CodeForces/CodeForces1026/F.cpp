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
	    cin >> n;
	    vector<int> a(n);
	    int ans = 0;
	    int mx = 0;
	    auto check = [&](int i) {
	        for(int j = 0; j < i; j++)
	            ans = max(ans, a[i]%a[j]+a[j]%a[i]);
	    };
	    
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
            if(a[i] > mx) {
                if(a[i] >= mx*2)
                    check(i);
                else
                    ans = max(ans, a[i]);
            }
            else {
                ans = max(ans, a[i]%mx + mx%a[i]);
            }
            mx = max(mx, a[i]);
	        cout << ans << " ";
	    }
	    cout << "\n";
	}
}