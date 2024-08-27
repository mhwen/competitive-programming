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
	ll sum = 0;
	ll m = 0;
	for(int i = 0; i < n; i++) {
		ll x;
		cin >> x;
		sum += x;
		m = max(m, x);
	}
	cout << sum-m << "\n";
}