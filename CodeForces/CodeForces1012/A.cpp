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
	vector<bool> prime(2e5, true);
	vector<int> primes;
	for(int i = 2; i < sz(prime); i++) {
	    if(prime[i]) {
	        primes.pb(i);
	        for(int j = i+i; j < sz(prime); j+=i)
	            prime[j] = false;
	    }
	}
	
	// auto check2 = [&](vector<int>& a, int n) {
        // cout << "checking n=" << n << endl;
        // int h;
        // if(sz(a) != n)
            // cout << "UH OH size is not right size:" << sz(a) << endl;
        // if((h = *min_element(all(a))) != 1) {
            // cout << "UH OH min is " << h << endl;
        // }
        // if((h = *max_element(all(a))) != n) {
            // cout << "UH OH max is " << h << endl;
        // }
        // set<int> seen;
        // ll sum = 0;
        // int cnt = 0;
        // for(int i = 0; i < sz(a); i++) {
            // if(seen.count(a[i]))
                // cout << "UH OH duplicates" << endl;
            // seen.insert(a[i]);
            // sum += a[i];
            // // cout << "sum: " << sum << " avg: " << (sum+i)/(i+1) << endl;
            // if(prime[(sum+i)/(i+1)])
                // cnt++;
        // }
        // if(cnt < n/3-1)
            // cout << "UH OH too few primes, need " << n/3-1 << " got " << cnt << endl;
    // };
	
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    
	    auto go = [&](int i) {
	        vector<bool> used(n+1);
	        vector<int> ans;
	        int make = 0;
	        for(int lo = 1; lo < i; lo++) {
	            if(lo*2 == i)
	                continue;
	            if(used[lo] || used[i-lo])
	                continue;
	            if(lo > n || i-lo > n)
	                continue;
	            used[lo] = used[i-lo] = true;
	            ans.pb(lo);
	            ans.pb(i-lo);
	            make++;
	        }
	        if(make < n/3-1)
	            return false;
	        for(int j = 1; j <= n; j++)
	            if(!used[j])
	                ans.pb(j);
	        // check2(ans, n);
	        for(auto a : ans)
	            cout << a << " ";
	        cout << "\n";
	        return true;
	    };
	    
	    int at = (int)(lower_bound(all(primes), n/2)-primes.begin());
	    for(int i = at-5; i <= at+5; i++) {
	        if(i < 0 || i > sz(primes))
	            continue;
	        if(go(2*primes[i])) {
	            break;
	        }
	    }
	}
}