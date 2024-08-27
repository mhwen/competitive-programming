#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll big = 6e8-1;
constexpr ll small = 5e8-1;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n;
		cin >> n;
		cout << big/n - small/n << "\n";
	}
}