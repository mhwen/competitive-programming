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
	    int n, m, k;
	    cin >> n >> m >> k;
	    vector<int> ans(n);
	    int step = max(k, n/(m+1));
	    for(int i = 0; i < step; i++) {
	        for(int j = i; j < n; j+=step) {
	            ans[j] = i;
	        }
	    }
	    for(auto a : ans)
	        cout << a << " ";
	    cout << "\n";
	}
	
}