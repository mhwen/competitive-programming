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
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	
	auto top = [&](int i) {
	    if(i == 0 || i == n-1)
	        return false;
	    return a[i]>a[i+1] && a[i]>a[i-1];
	};
	auto bot = [&](int i) {
	    if(i == 0 || i == n-1)
	        return false;
	    return a[i]<a[i+1] && a[i]<a[i-1];
	};
	ll ans = 0;
	for(int i = 0; i < n; i++) {
	    if(top(i)) {
    	    int j = i;
	        while(j < n && !bot(j))
	            j++;
	        if(j < n) {
	            int l = i;
    	        while(l-1 >= 0 && a[l-1]<a[l]) l--;
	            int r = j;
	            while(r+1 < n && a[r+1]>a[r]) r++;
	            int lo = i-l;
	            int hi = r-j;
	            ans += (ll)lo*hi;
	        }
	    }
	}
	cout << ans << "\n";
}