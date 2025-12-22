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
	vector<pair<int, int>> events;
	for(int i = 0; i < n; i++) {
	    int l, r;
	    cin >> l >> r;
	    events.emplace_back(l, 1);
	    events.emplace_back(r+1, -1);
	}
	vector<int> ans(q);
	for(int i = 0; i < q; i++) {
	    int t;
	    cin >> t;
	    events.emplace_back(t, i+2);
	}
	sort(all(events));
	int amt = 0;
	for(auto [_, t] : events) {
	    if(t < 2)
	        amt += t;
	    else
	        ans[t-2] = amt;
	}
	for(auto a : ans)
	    cout << a << "\n";
}