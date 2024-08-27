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
	ll adds = 0, removes = 0;
	ll diff = 0;
	for(int i = 0; i < n; i++) {
		diff += adds-removes;
		ll val;
		cin >> val;
		val += diff;
		if(val < 0) {
			adds += abs(val);
			diff += abs(val);
		}
		else if(val > 0) {
			removes += val;
			diff -= val;
		}
	}
	cout << adds+removes << "\n";
}