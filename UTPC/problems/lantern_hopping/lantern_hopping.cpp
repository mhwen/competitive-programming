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
	int n, q;
	cin >> n >> q;
	vector<int> nums(n);
    multiset<int> seen;
	for(int i = 0; i < n; i++) {
	    cin >> nums[i];
	    seen.insert(nums[i]);
	}
	while(q-->0) {
	    int t, p;
	    cin >> t >> p;
	    p--;
	    if(t == 1)
	        cout << *seen.rbegin()-nums[p] << "\n";
	    else {
	        int x;
	        cin >> x;
	        seen.erase(seen.find(nums[p]));
	        nums[p] = x;
	        seen.insert(nums[p]);
	    }
	}
}