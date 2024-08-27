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
	ll best = 0;
	ll curr = 0;
	vector<ll> tastes(n);
	ll sum = 0;
	for(int i = 0; i < n; i++) {
		cin >> tastes[i];
		sum += tastes[i];
		curr += tastes[i]*(i+1);
	}
	best = max(best, curr);
	for(int i = 1; i < n; i++) {
		curr -= sum;
		curr += tastes[i-1]*n;
		best = max(best, curr);
	}
	cout << best << "\n";
}