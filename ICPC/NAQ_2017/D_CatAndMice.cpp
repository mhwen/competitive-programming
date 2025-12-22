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

constexpr ld INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ld> x(n);
	vector<ld> y(n);
	vector<ld> s(n);
	for(int i = 0; i < n; i++)
		cin >> x[i] >> y[i] >> s[i];
	ld R;
	cin >> R;
	
	auto timeToReach = [&](ld x1, ld y1, ld x2, ld y2, ld speed) {
		ld dx = x2-x1;
		ld dy = y2-y1;
		ld dist = sqrt(dx*dx+dy*dy);
		return dist/speed;
	};
	
	auto check = [&](ld speed) {
		vector<vector<ld>> dp(n, vector<ld>(1<<n, INF));
		for(int i = 0; i < n; i++) {
			int mask = (1<<i);
			ld time = timeToReach(0, 0, x[i], y[i], speed);
			if(time <= s[i])
				dp[i][mask] = time;
			else
				return false;
		}
		for(int mask = 1; mask < (1<<n); mask++) {
			int taken = __builtin_popcount(mask);
			ld S = speed*pow(R, taken);
			for(int curr = 0; curr < n; curr++) {
				if((mask&(1<<curr))==0)
					continue;
				if(dp[curr][mask] == INF)
					continue;
				for(int next = 0; next < n; next++) {
					if(mask&(1<<next))
						continue;
					int newMask = mask|(1<<next);
					ld time = timeToReach(x[curr], y[curr], x[next], y[next], S);
					ld reach = time+dp[curr][mask];
					if(reach <= s[next])
						dp[next][newMask] = min(dp[next][newMask], reach);
				}
			}
		}
		bool found = false;
		int want = (1<<n)-1;
		for(int i = 0; i < n; i++)
			if(dp[i][want] != INF)
				found = true;
		return found;
	};
	ld l = 0, r = 1e8;
	for(int its = 0; its < 60; its++) {
		ld mid = (l+r)/2;
		if(check(mid))
			r = mid;
		else
			l = mid;
	}
	cout << fixed << setprecision(20) << (l+r)/2 << "\n";
}