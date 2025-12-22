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
		int len = 1;
		char prev = s[0];
		int ans = 0;
		if(s.front() == '_')
			ans++;
		if(s.back() == '_')
			ans++;
		for(int i = 1; i < sz(s); i++) {
			if(s[i] == prev)
				len++;
			else {
				if(prev == '_')
					ans += len-1;
				len = 1;
				prev = s[i];
			}
		}
		if(prev == '_')
			ans += len-1;
		if(sz(s) == 1 && s[0] == '^')
			ans++;
		cout << ans << "\n";
	}
}