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
#include <random>
#include <chrono>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll randval(ll n) {
	return uniform_int_distribution(1LL, n)(rng);
}

int n;

ll check(vector<pair<ll, ll>> cows) {
	vector<ll> sufSum(n);
	for(int i = n-1; i >= 0; i--) {
		sufSum[i] = cows[i].second;
		if(i < n-1)
			sufSum[i] += sufSum[i+1];
	}
	ll sum = 0;
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		sum += cows[i].first;
		ans = max(ans, sum+sufSum[i]);
	}
	return ans;
}

ll solve(vector<pair<ll, ll>> cows) {
	vector<pair<ll, ll>> neg;
	vector<pair<ll, ll>> pos;
	for(auto cow : cows) {
		if(cow.first < cow.second)
			neg.push_back(cow);
		else
			pos.push_back(cow);
	}
	sort(all(neg), [](auto a, auto b){
		return a.first < b.first;
	});
	sort(all(pos), [](auto a, auto b){
		return a.second > b.second;
	});
	neg.insert(neg.end(), pos.begin(), pos.end());
	return check(neg);
}

// ll solve_slow(vector<pair<ll, ll>> cows) {
	// sort(all(cows));
// 	
	// ll best = check(cows);
	// do {
		// best = min(best, check(cows));
	// }
	// while(next_permutation(all(cows)));
	// return best;
// }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<pair<ll, ll>> cows(n);
	for(int i = 0; i < n; i++) {
		cin >> cows[i].first >> cows[i].second;
	}
	cout << solve(cows);
}