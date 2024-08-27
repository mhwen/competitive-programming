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
	int n;
	cin >> n;
	int maskSize = 1;
	for(int i = 0; i < 7; i++) {
		maskSize *= 3;
	}
	vector<int> threePows(7);
	threePows[0] = 1;
	for(int i = 1; i < 7; i++) {
		threePows[i] = threePows[i-1]*3;
	}
	vector<ll> dp(maskSize);
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		vector<int> add(7);
		for(int j = 0; j < 7; j++)
			cin >> add[j];
		ll val;
		cin >> val;
		for(int mask = maskSize-1; mask >= 0; mask--) {
			int hold = mask;
			int newMask = 0;
			bool good = true;
			for(int j = 0; j < 7; j++) {
				int used = hold%3;
				hold /= 3;
				if(used+add[j] < 3) {
					newMask += threePows[j]*(used+add[j]);
				}
				else
					good = false;
			}
			if(good) {
				dp[newMask] = max(dp[newMask], dp[mask]+val);
				ans = max(ans, dp[newMask]);
			}
		}
	}
	cout << ans << "\n";
}