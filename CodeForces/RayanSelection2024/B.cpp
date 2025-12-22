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
		int n, m, k;
		cin >> n >> m >> k;
		string s;
		cin >> s;
		int cnt = 0;
		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == '0') {
				cnt++;
				if(cnt == m) {
					ans++;
					i+=k-1;
					cnt = 0;
				}
			}
			else
				cnt = 0;
		}
		cout << ans << "\n";
	}
}