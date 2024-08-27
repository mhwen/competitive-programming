#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll m, k;
		cin >> n >> m >> k;
		vector<ll> tickets(n);
		for(int i = 0; i < n; i++) {
			cin >> tickets[i];
		}
		sort(tickets.begin(), tickets.end());
		ll cost = 0;
		ll bought = 0;
		for(int i = 0; i < n; i++) {
			if(k > 0) {
				ll buy = min(k, m);
				cost += (bought+tickets[i])*buy;
				k -= buy;
				bought += buy;
			}
		}
		cout << cost << "\n";
	}
}