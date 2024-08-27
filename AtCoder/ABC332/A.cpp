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
	int n;
	ll s, k;
	cin >> n >> s >> k;
	ll sum = 0;
	for(int i = 0; i < n; i++) {
		ll p, q;
		cin >> p >> q;
		sum += p*q;
	}
	if(sum < s)
		sum += k;
	cout << sum << "\n";
}