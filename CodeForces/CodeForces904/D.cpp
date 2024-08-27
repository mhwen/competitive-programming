#include <iostream>
#include <vector>
#include <algorithm>

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
		vector<ll> counts(n+1);
		for(int i = 0; i < n; i++) {
			ll num;
			cin >> num;
			counts[num]++;
		}
		vector<ll> badPairs(n+1);
		for(int i = n; i >= 1; i--) {
			ll count = 0;
			ll ignore = 0;
			int hold = i;
			while(hold <= n) {
				count += counts[hold];
				ignore += badPairs[hold];
				hold += i;
			}
			badPairs[i] = count*(count-1)/2-ignore;
		}
		vector<bool> used(n+1);
		ll goodPairs = ((ll)n)*(n-1)/2;
		for(int i = 1; i <= n; i++) {
			if(counts[i] > 0 && !used[i]) {
				int hold = i;
				while(hold <= n) {
					if(!used[hold]) {
						used[hold] = true;
						goodPairs -= badPairs[hold];
					}
					hold += i;
				}
			}
		}
		cout << goodPairs << "\n";
	}
}