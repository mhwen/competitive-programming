#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;
constexpr int MOD = 1e9+7;

ll fac[1000000];
ll invFac[1000000];


ll pow(ll a, ll p) {
	if(p == 0)
		return 1;
	ll res = pow(a, p/2);
	if(p%2==1)
		return res*res%MOD*a%MOD;
	return res*res%MOD;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

ll choose(int a, int b) {
	return fac[a]*invFac[b]%MOD*invFac[a-b]%MOD;
}

int main() {
	
	fac[0] = 1;
	for(int i = 1; i < 1000000; i++) {
		fac[i] = fac[i-1]*i%MOD;
	}
	for(int i = 0; i < 1000000; i++) {
		invFac[i] = inv(fac[i]);
	}
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<ll> earns(n);
	for(int i = 0; i < n; i++) {
		cin >> earns[i];
	}
	vector<ll> costs(m);
	for(int i = 0; i < m; i++) {
		cin >> costs[i];
	}
	sort(earns.rbegin(), earns.rend());
	sort(costs.begin(), costs.end());
	ll ways = 1;
	ll sold = 1;
	ll profit = 0;
	ll greatestCost = -1;
	ll smallestProfit = 2e9;
	int numLargestCostTaken = 0;
	int numSmallestProfitTaken = 0;
	for(int i = 0; i < min(n, m); i++) {
		if(earns[i] >= costs[i]*2) {
			profit += earns[i]-costs[i]*2;
			ways = ways*sold%MOD;
			sold++;
			if(costs[i] == greatestCost) {
				numLargestCostTaken++;
			}
			else if(costs[i] > greatestCost) {
				greatestCost = costs[i];
				numLargestCostTaken = 1;
			}
			if(earns[i] == smallestProfit) {
				numSmallestProfitTaken++;
			}
			else if(earns[i] < smallestProfit) {
				smallestProfit = earns[i];
				numSmallestProfitTaken = 1;
			}
		}
	}
	
	int totalLargestCost = (int)count(costs.begin(), costs.end(), greatestCost);
	int totalSmallestProfit = (int)count(earns.begin(), earns.end(), smallestProfit);
	ll chooseCosts = choose(totalLargestCost, numLargestCostTaken);
	ll chooseProfits = choose(totalSmallestProfit, numSmallestProfitTaken);
	cout << setprecision(20) << ((ld)profit)/2 << " " << ways*chooseCosts%MOD*chooseProfits%MOD << "\n";
	// cout << setprecision(20) << ((ld)profit)/2 << " " << ways << "\n";
}