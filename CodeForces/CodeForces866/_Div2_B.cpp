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
		string s;
		cin >> s;
		int ones = 0;
		for(char c : s) {
			if(c == '1')
				ones++;
		}
		if(ones == sz(s)) {
			cout << (ll)sz(s)*sz(s) << "\n";
			continue;
		}
		s += s;
		int prev = s.front();
		ll len = 1;
		ll ans = 0;
		for(int i = 1; i < sz(s); i++) {
			if(s[i] == prev)
				len++;
			else {
				if(prev == '1')
					ans = max(ans, ((len+1)/2)*((len+2)/2));
				prev = s[i];
				len = 1;
			}
		}
		if(prev == '1')
			ans = max(ans, ((len+1)/2)*((len+2)/2));
		cout << ans << "\n";
	}
}