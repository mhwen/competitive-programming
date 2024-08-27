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
		ll n;
		int m, k;
		cin >> n >> m >> k;
		vector<vector<ll>> evens(m);
		vector<vector<ll>> odds(m);
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < k; j++) {
				ll val;
				cin >> val;
				if(val%2==0)
					evens[i].push_back(val);
				else
					odds[i].push_back(val);
			}
			sort(evens[i].begin(), evens[i].end());
			sort(odds[i].begin(), odds[i].end());
		}
		vector<ll> delta(m);
		vector<ll> remaining(m);
		ll curr = n;
		vector<string> choice(m);
		bool bad = false;
		vector<ll> amountAfterRound(m); //*******//
		for(int i = 0; i < m; i++) {
			if(evens[i].empty()) {
				choice[i] = "Odd";
				delta[i] = odds[i].front();
			}
			else if(odds[i].empty()) {
				choice[i] = "Even";
				delta[i] = evens[i].front();
			}
			else {
				if(evens[i].back() > odds[i].back()) {
					choice[i] = "Even";
					delta[i] = -odds[i].back();
				}
				else {
					choice[i] = "Odd";
					delta[i] = -evens[i].back();
				}
			}
			curr += delta[i];
			remaining[i] = curr;
			amountAfterRound[i] = curr; //~~~~~~~~//
			if(curr <= 0) {
				bad = true;
				break;
			}
		}
		if(bad) {
			cout << -1 << "\n";
			continue;
		}
		
		//~~~~~~~~//
		vector<ll> suffixMin(m);
		suffixMin[m-1] = amountAfterRound[m-1];
		for(int i = m-2; i >= 0; i--) {
			suffixMin[i] = min(suffixMin[i+1], amountAfterRound[i]);
		}
		//~~~~~~~~//
		
		ll loss = 0;
		for(int i = 0; i < m; i++) {
			if(choice[i] == "Odd") {
				ll newDelta = -odds[i].back();
				ll diff = newDelta-delta[i];
				if(suffixMin[i]+loss+diff > 0) { //~~~~~~~~//
					choice[i] = "Even";
					loss += diff;
				}
			}
		}
		for(int i = 0; i < m; i++) {
			if(i > 0)
				cout << " ";
			cout << choice[i];
		}
		cout << "\n";
	}
}