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
	    vector<int> a(n);
	    for(int i = 0; i < n; i++) 
	        cin >> a[i];
	    bool bad = false;
	    for(int i = 0; i < n; i++) {
	        int left = i*2;
	        int right = (n-i-1)*2;
	        if(a[i] <= max(left, right))
	            bad = true;
	    }
	    if(bad)
	        cout << "NO\n";
	    else
	        cout << "YES\n";
	}
}