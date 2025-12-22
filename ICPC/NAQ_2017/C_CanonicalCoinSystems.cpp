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

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> coins(n);
	for(int& i : coins)
		cin >> i;
	int MAX = coins.back()*2+1;
	vector<int> dp(MAX, INF);
	vector<int> greedy(MAX, INF);
	dp[0] = greedy[0] = 0;
	for(int i = 0; i < n; i++) {
		vector<int> newDp(MAX, INF);
		vector<int> newGreedy(MAX, INF);
		int val = coins[i];
		for(int j = 0; j < MAX; j++) {
			newDp[j] = dp[j];
			if(j >= val)
				newDp[j] = min(newDp[j], newDp[j-val]+1);
			newGreedy[j] = greedy[j%val]+j/val;
		}
		dp = newDp;
		greedy = newGreedy;
	}
	bool found = false;
	for(int i = 0; i < MAX; i++) {
		if(dp[i] != greedy[i])
			found = true;
	}
	if(found)
		cout << "non-canonical\n";
	else
		cout << "canonical\n";
}