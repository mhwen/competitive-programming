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
	vector<int> x(n);
	for(int i = 0; i < n; i++)
	    cin >> x[i];
	int ans = -1;
	auto check = [&](int p) {
	    int len = 1;
	    while(p-len >= 0 && p+len < n) {
	        int lo = p-len;
	        int hi = p+len;
	        if(x[lo]<x[lo+1] && x[hi]<x[hi-1] && x[lo]==x[hi])
	            len++;
	        else
	            break;
	    }
	    if(len > 1)
	        ans = max(ans, 2*len-1);
	};
	
	for(int i = 1; i < n-1; i++) {
	    if(x[i]>x[i+1] && x[i]>x[i-1])
	        check(i);
	}
	cout << ans << "\n";
}