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

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<int>> f(1e6+5);
	vector<vector<int>> from(1e6+5);
	for(int i = 2; i < sz(f); i++) {
		if(f[i].empty()) {
			for(int j = i; j < sz(f); j+=i)
				f[j].push_back(i);
		}
		for(int mask = 1; mask < (1<<sz(f[i])); mask++) {
			int val = -1;
			for(int bit = 0; bit < sz(f[i]); bit++) {
				if(mask&(1<<bit)) {
					val *= -f[i][bit];
				}
			}
			from[i].push_back(val);
		}
	}
	vector<ll> cnt(1e6+5);
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(auto& a : nums)
		cin >> a;
	
	for(int i = 0; i < n; i++) {
		ll v = nums[i];
		ll w = 0;
		for(auto F : from[v]) {
			if(F < 0)
				w = (w-cnt[-F]+MOD)%MOD;
			else
				w = (w+cnt[F])%MOD;
		}
		if(i == 0)
			w++;
		for(auto F : from[v])
			cnt[abs(F)] = (cnt[abs(F)]+w)%MOD;
		if(i == n-1)
			cout << w << "\n";
	}
}