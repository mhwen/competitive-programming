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

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	int size = n*(int)1e5+5;
	vector<int> dp(size, INF);
	dp[0] = 0;
	for(int x = 0; x < n; x++) {
	    int a, b;
	    cin >> a >> b;
	    vector<int> newDp(size, INF);
	    for(int i = 0; i < sz(newDp); i++) {
	        if(dp[i] == INF)
	            continue;
	        newDp[i] = min(newDp[i], dp[i]+b);
	        newDp[i+a] = min(newDp[i+a], dp[i]);
	    }
	    dp = newDp;
	}
	int best = INF;
	for(int i = 0; i < sz(dp); i++)
	    best = min(best, max(i, dp[i]));
	cout << best << "\n";
	
}