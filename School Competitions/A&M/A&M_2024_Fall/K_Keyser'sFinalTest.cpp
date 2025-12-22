#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> even;
	vector<ll> odd;
	for(int i = 0; i < n; i++) {
		ll l;
		cin >> l;
		if(l%2)
			odd.push_back(l);
		else
			even.push_back(l);
	}
	sort(all(even));
	reverse(all(even));
	sort(all(odd));
	for(int i = 0; i < k; i++) {
		if(sz(even)) {
			cout << even.back() << " ";
			even.pop_back();
		}
		else {
			cout << odd.back() << " ";
			odd.pop_back();
		}
	}
	cout << "\n";
}