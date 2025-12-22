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
	    int n, k;
	    cin >> n >> k;
	    vector<int> nums(n);
	    for(int i = 0; i < n; i++) {
	        cin >> nums[i];
	    }
	    int L = n;
	    int rem = k;
	    for(int i = 0; i < n; i++) {
	        if(nums[i] == nums[0])
	            rem--;
	        if(rem == 0) {
	            L = i;
	            break;
	        }
	    }
	    if(nums[0] == nums[n-1] && L < n) {
	        cout << "YES\n";
	        continue;
	    }
	    rem = k;
	    int R = -1;
	    for(int i = n-1; i >= 0; i--) {
	        if(nums[i] == nums[n-1])
	            rem--;
	        if(rem == 0) {
	            R = i;
	            break;
	        }
	    }
	    if(L < R)
	        cout << "YES\n";
	    else
	        cout << "NO\n";
	}
}