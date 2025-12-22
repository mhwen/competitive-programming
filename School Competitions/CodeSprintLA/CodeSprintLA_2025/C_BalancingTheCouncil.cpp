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
	ll n, m;
	cin >> n >> m;
	ll N = n;
	if(m%2==0) {
	    cout << "Yes\n";
	    return 0;
	}
	vector<bool> prime(2e5, true);
	bool good = false;
	for(int i = 2; i < sz(prime); i++) {
	    if(prime[i]) {
	        for(int j = i+i; j < sz(prime); j+=i)
	            prime[j] = false;
	        if(i%2==1 && n%i==0) {
	            if(m%i==0)
	                good = true;
	            ll rem = m-i;
	            ll available = N-2*i;
	            if(rem <= available && rem >= 0)
	                good = true;
	        }
	        while(n%i==0)
	            n/=i;
	    }
	}
	if(n > 1) {
	    if(m%n==0)
            good = true;
        ll rem = m-n;
        ll available = N-2*n;
        if(rem <= available && rem >= 0)
            good = true;
	}
	if(good)
	    cout << "Yes\n";
	else
	    cout << "No\n";
}