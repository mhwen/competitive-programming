#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		set<pair<int, int>> state;
		for(int i = 1; i <= k; i++) {
			state.insert({0, i});
		}
		// int best = 0;
		for(int i = 0; i < n; i++) {
			int val;
			cin >> val;
			pair<int, int> next;
			if(val == 1) {
				next = *state.begin();
			}
			else {
				next = *state.rbegin();
			}
			state.erase(next);
			cout << next.second << " ";
			// best = max(best, next.first+val);
			state.insert({max(0, next.first+val), next.second});

		}
		cout << "\n";
		// cout << best << endl;
	}
}