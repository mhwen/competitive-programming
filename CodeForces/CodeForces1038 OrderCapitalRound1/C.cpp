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
	    vector<pair<int, int>> X(n);
	    vector<pair<int, int>> Y(n);
	    for(int i = 0; i < n; i++) {
	        int x, y;
	        cin >> x >> y;
	        X[i] = {x, i};
	        Y[i] = {y, i};
	    }
	    sort(all(X));
	    sort(all(Y));
	    vector<int> type(n);
	    for(int i = 0 ; i < n/2; i++) {
	        type[X[i].second] |= 1;
	        type[Y[i].second] |= 2;
	    }
	    vector<vector<int>> group(4);
	    for(int i = 0; i < n; i++) {
	        group[type[i]].pb(i);
	    }
	    assert(sz(group[0]) == sz(group[3]));
	    assert(sz(group[1]) == sz(group[2]));
	    auto go = [&](int A, int B) {
	        while(!group[A].empty()) {
    	        int a = group[A].back();
    	        int b = group[B].back();
    	        group[A].pop_back();
    	        group[B].pop_back();
    	        cout << a+1 << " " << b+1 << "\n";
	        }
	    };
	    go(0, 3);
	    go(1, 2);
	}
}