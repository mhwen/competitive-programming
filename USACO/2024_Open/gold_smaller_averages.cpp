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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> b(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		cin >> b[i];
	vector<int> preA(n+1);
	vector<int> preB(n+1);
	for(int i = 0; i < n; i++) {
		preA[i+1] = preA[i]+a[i];
		preB[i+1] = preB[i]+b[i];
	}
	
	auto cmp = [](pair<pair<int, int>, int> aa, pair<pair<int, int>, int> bb){
		auto A = aa.first;
		auto B = bb.first;
		return (ll)A.first*B.second <= (ll)B.first*A.second;
	};
	
	//bSuffs[i] = sorted suffixes of b[1..i]
	vector<vector<pair<pair<int, int>, int>>> bSuffs(n+1);
	for(int i = 1; i <= n; i++) {
		for(int left = 0; left < i; left++) {
			bSuffs[i].push_back({{preB[i]-preB[left], i-left}, left});
		}
		sort(all(bSuffs[i]), cmp);
		reverse(all(bSuffs[i]));
	}
	
	//bSums[i][j][id] = Presum of dp[i][1..id] for id in bSuffs[j][1..j]
	vector bSums(n+1, vector(n+1, vector<int>(1)));
	vector<int> dp(n+1);
	dp[0] = 1;
	
	auto update = [&](int i) {
		for(int j = 1; j <= n; j++) {
			for(auto B : bSuffs[j])
				bSums[i][j].push_back((bSums[i][j].back()+dp[B.second])%MOD);
		}
	};
	
	//Update bSums
	update(0);
	
	for(int i = 1; i <= n; i++) {
		vector<pair<pair<int, int>, int>> aSuff;
		for(int left = 0; left < i; left++) {
			aSuff.push_back({{preA[i]-preA[left], i-left}, left});
		}
		sort(all(aSuff), cmp);
		vector<int> newDp(n+1);
		for(int j = 1; j <= n; j++) {
			auto& bSuff = bSuffs[j];
			int B = sz(bSuff)-1;
			for(int A = 0; A < sz(aSuff); A++) {
				while(B >= 0 && !cmp(aSuff[A], bSuff[B]))
					B--;
				newDp[j] += bSums[aSuff[A].second][j][B+1];
				newDp[j] %= MOD;
			}
		}
		//Update bSums
		dp = newDp;
		update(i);
	}
	cout << dp[n] << "\n";
}