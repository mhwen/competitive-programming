#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
constexpr int MAXN = 1e5+5;
constexpr ll MOD = 1000000007;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<ll> dp(MAXN);
	dp[1] = 1;
	ll evenSum = 0, oddSum = 0;
	for(int i = 1; i < (int)dp.size(); i++) {
		if(i%2==0) {
			dp[i] = (evenSum+2)%MOD;
			evenSum = (evenSum+dp[i])%MOD;
		}
		else {
			dp[i] = (oddSum+1)%MOD;
			oddSum = (oddSum+dp[i])%MOD;
		}
	}

	vector<ll> total(MAXN);
	ll sum = 0;
	for(int i = 1; i < (int)total.size(); i++) {
		total[i] = (sum+1)%MOD;
		sum = (sum+total[i])%MOD;
	}
	vector<ll> preSum(MAXN+1);
	for(int i = 1; i <= MAXN; i++) {
		preSum[i] = (preSum[i-1]+(total[i]-dp[i])+MOD)%MOD;
	}
	
	int t;
	cin >> t;
	while(t-->0) {
		int l, r;
		cin >> l >> r;
		cout << (preSum[r]-preSum[l-1]+MOD)%MOD << "\n";
	}
}