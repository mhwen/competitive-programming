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
	int t;
	cin >> t;
	while(t-->0) {
		ll n, k;
		cin >> n >> k;
		if(k == 1) {
			cout << "YES\n";
			cout << 1 << "\n";
			cout << n << "\n";
		}
		else if(k == n) {
			cout << "YES\n";
			cout << 1 << "\n";
			cout << 1 << "\n";
		}
		else {
			ll take = n-(k-1);
			if(take*2 > n) {
				cout << "YES\n";
				cout << 2 << "\n";
				cout << take << " " << 1 << "\n";
			}
			else {
				cout << "NO\n";
			}
		}
	}
}