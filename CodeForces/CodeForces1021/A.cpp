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
	    map<int, int> freq;
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        freq[a[i]]++;
	    }
	    int prev = -1;
	    bool twoSeen = false;
	    bool good = false;
	    for(auto [v, cnt] : freq) {
	        if(cnt >= 4)
	            good = true;
	        if(v == prev+1) {
	            if(twoSeen && cnt >= 2)
	                good = true;
	        }
	        else {
	            twoSeen = false;
	        }
	        if(cnt >= 2)
	            twoSeen = true;
	        prev = v;
	    }
	    if(good)
	        cout << "Yes\n";
	    else
	        cout << "No\n";
	}
}