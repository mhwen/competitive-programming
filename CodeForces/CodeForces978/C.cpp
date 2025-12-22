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
		int n;
		cin >> n;
		vector<string> s(2);
		cin >> s[0] >> s[1];
		
		auto v = [&](int r, int c) {
			if(c >= sz(s[r]))
				return 0;
			return s[r][c] == 'A' ? 1 : 0;
		};
		
		auto check = [&](int num) {
			return num > 1 ? 1 : 0;
		};
		
		auto check3 = [&](int r, int c) {
			return check(v(r,c)+v(r,c+1)+v(r,c+2));
		};
		auto checklt = [&](int c) {
			return check(v(0,c)+v(0,c+1)+v(1,c));
		};
		auto checklb = [&](int c) {
			return check(v(0,c)+v(1,c)+v(1,c+1));
		};
		auto checkrt = [&](int c) {
			return check(v(0,c-1)+v(0,c)+v(1,c));
		};
		auto checkrb = [&](int c) {
			return check(v(0,c)+v(1,c-1)+v(1,c));
		};
		
		map<pair<int, int>, int> dp;
		dp[{0, 0}] = 0;
		for(int i = 0; i < n; i++) {
			for(int j = max(0, i-1); j <= min(n-1, i+1); j++) {
				if(dp.count({i, j})) {
					int curr = dp[{i, j}];
					dp[{i+3, j+3}] = max(dp[{i+3, j+3}], curr+check3(0,i)+check3(1,j));
					if(i == j) {
						dp[{i+2, j+1}] = max(dp[{i+2, j+1}], curr+checklt(i));
						dp[{i+1, j+2}] = max(dp[{i+1, j+2}], curr+checklb(i));
					}
					else if(i < j)
						dp[{i+2, j+1}] = max(dp[{i+2, j+1}], curr+checkrt(j));
					else
						dp[{i+1, j+2}] = max(dp[{i+1, j+2}], curr+checkrb(i));
				}
			}
		}
		cout << dp[{n, n}] << "\n";
	}
}