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
	int n;
	ll m;
	cin >> n >> m;
	vector<ll> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	auto get = [&](int l, int r) {
	    set<ll> s;
	    s.insert(0);
	    for(int i = l; i < r; i++) {
	        set<ll> next;
	        for(auto num : s) {
	            next.insert(num);
	            next.insert((num+a[i])%m);
	        }
	        s = next;
	    }
	    return s;
	};
	auto left = get(0, n/2);
	auto right = get(n/2, n);
	ll best = 0;
	for(auto num : left) {
	    ll mx = m-num;
	    auto it = right.lower_bound(mx);
	    if(it != right.begin()) {
	        it--;
	        best = max(best, num+*it);
	    }
	}
	swap(left, right);
	for(auto num : left) {
	    ll mx = m-num;
	    auto it = right.lower_bound(mx);
	    if(it != right.begin()) {
	        it--;
	        best = max(best, num+*it);
	    }
	}
	cout << best << "\n";
}