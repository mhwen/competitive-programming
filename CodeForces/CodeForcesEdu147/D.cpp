#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k;
		cin >> n >> k;
		vector<ll> left(n);
		vector<ll> len(n);
		for(int i = 0; i < n; i++) {
			cin >> left[i];
		}
		vector<ll> right(n);
		for(int i = 0; i < n; i++) {
			cin >> right[i];
			len[i] = right[i]-left[i]+1;
		}
		ll curr = 0;
		ll best = 2e18;
		int taken = 0;
		int ones = 0;
		for(int i = 0; i < n; i++) {
			if(len[i] >= 2) {
				taken++;
				curr += len[i];

			}
			else {
				ones++;
			}
			if(curr+ones >= k) {
				if(curr >= k) {
					best = min(best, right[i]-(curr-k) + taken*2);
				}
				else {
					ll onesNeeded = k-curr;
					best = min(best, right[i] + (taken+onesNeeded)*2);
				}
			}
		}
		
		if(best == (ll)2e18)
			cout << "-1\n";
		else
			cout << best << "\n";
	}
}