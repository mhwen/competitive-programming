#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
typedef long long ll;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<pair<ll, ll>> gifts;
		multiset<ll> bPos;
		for(int i = 0; i < n; i++) {
			ll a, b;
			cin >> a >> b;
			gifts.push_back({a, b});
			bPos.insert(b);
		}
		
		sort(gifts.begin(), gifts.end());
		ll bVal = -2e9;
		int bCurr = n-1;
		ll ans = 2e9+1;
		for(int i = n-1; i >= 0; i--) {
			ll aVal = gifts[i].first;
			while(bCurr > i && gifts[i].first < gifts[bCurr].first) {
				bVal = max(bVal, gifts[bCurr].second);
				bPos.erase(bPos.find(gifts[bCurr].second));
				bCurr--;
			}
			ans = min(ans, abs(bVal-aVal));

			bPos.erase(bPos.find(gifts[i].second));
			auto take = bPos.upper_bound(aVal);
			if(take != bPos.end()) {
				ll bTake = max(bVal, *take);
				ans = min(ans, abs(aVal-bTake));
			}
			if(take != bPos.begin()) {
				take--;
				ll bTake = max(bVal, *take);
				ans = min(ans, abs(aVal-bTake));
			}
			bPos.insert(gifts[i].second);
		}
		
		cout << ans << "\n";
	}
}