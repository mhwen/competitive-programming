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
	set<int> seen;
	vector<ll> below(n, 1);
	vector<ll> above(n, 1);
	ll best = 0;
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		num--;
		auto upper = seen.upper_bound(num);
		if(upper != seen.end()) {
			above[num] += above[*upper];
		}
		if(upper != seen.begin()) {
			upper--;
			below[num] += below[*upper];
		}
		seen.insert(num);
		best = max(best, above[num]+below[num]-1);
	}
	cout << best << "\n";
}