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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll m;
		cin >> n >> m;
		map<ll, ll> freq;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			ll num;
			cin >> num;
			freq[num]++;
		}
		ll best = 0;
		for(auto [a,cnt1]:freq) {
			ll used1 = min(m/a, cnt1);
			best = max(best, a*used1);
			if(freq.count(a+1)) {
				ll cnt2 = freq[a+1];
				ll extra = m-a*used1;
				ll used2 = min(extra/(a+1), cnt2);
				ll ans = a*used1+(a+1)*used2;
				best = max(best, ans);
				ll slack = m-ans;
				ll unused2 = cnt2-used2;
				slack -= min(used1, unused2);
				slack = max(0LL, slack);
				best = max(best, m-slack);
			}
		}
		cout << best << "\n";
	}
}