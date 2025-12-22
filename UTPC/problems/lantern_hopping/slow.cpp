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
	vector<ll> nums(n);
	for(int i = 0; i < n; i++)
	    cin >> nums[i];
	    
	auto solveLeft = [&](int i) {
	    ll worst = 0;
	    ll curr = 0;
	    while(i > 0) {
	        curr += nums[i]-nums[i-1];
	        worst = min(worst, curr);
	        i--;
	    }
	    return -worst;
	};
	
	auto solveRight = [&](int i) {
	    ll worst = 0;
	    ll curr = 0;
	    while(i < n-1) {
	        curr += nums[i]-nums[i+1];
	        worst = min(worst, curr);
	        i++;
	    }
	    return -worst;
	};
	
	while(q-->0) {
	    int type;
	    cin >> type;
	    if(type == 1) {
	        int p;
	        cin >> p;
	        p--;
	        cout << max(solveLeft(p), solveRight(p)) << "\n";
	    }
	    else {
	        int p;
	        ll x;
	        cin >> p >> x;
	        p--;
	        nums[p] = x;
	    }
	}
}