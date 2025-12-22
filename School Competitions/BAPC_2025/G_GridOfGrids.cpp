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
	int n, m;
	cin >> n >> m;
	map<int, ll> cnts;
	for(int i = 0; i < n; i++) {
	    int v = 0;
	    for(int j = 0; j < m*m; j++) {
	        char c;
	        cin >> c;
	        v *= 2;
	        if(c == 'X')
	            v++;
	    }
	    cnts[v]++;
	}
	ll ans = 0;
	for(auto [v, cnt] : cnts) {
	    ans += cnt*(cnt-1)/2;
	}
	ll nonZero = n-cnts[0];
	ans += nonZero*cnts[0];
	cout << ans << "\n";
}