#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	ll prev = 0, prev2 = 0;
	for(int i = 0; i < n; i++) {
		ll b;
		cin >> b;
		ll next = max(prev, prev2+b);
		prev2 = prev;
		prev = next;
	}
	cout << max(prev, prev2) << "\n";
}