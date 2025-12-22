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

ll choose(int n, int k) {
    ll res = 1;
    for(int i = 1; i <= k; i++) {
        res = res*(n-i+1)/i;
    }
    return res;
}

int main() {
    
    vector c(51, vector<ll>(51));
    for(int len = 0; len <= 50; len++) {
        for(int k = 0; k <= len; k++)
            c[len][k] = choose(len, k);
    }
    
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<ll> nums(n);
	    for(int i = 0; i < n; i++)
	        cin >> nums[i];
	        
	    auto eval = [&](int l, int r) {
	        int len = r-l;
	        ll sum = 0;
	        for(int i = 0; i <= len; i++) {
	            if(i%2==0)
	                sum += nums[l+i]*c[len][i];
	            else
	                sum -= nums[l+i]*c[len][i];
	        }
	        return sum;
	    };
	    ll best = accumulate(all(nums), 0LL);
	    for(int len = 1; len < n; len++) {
	        ll sum = 0;
	        for(int i = 0; i+len < n; i++) {
	            sum += eval(i, i+len);
	        }
	        best = max(best, sum);
	        best = max(best, -sum);
	    }
	    cout << best << "\n";
	}
}