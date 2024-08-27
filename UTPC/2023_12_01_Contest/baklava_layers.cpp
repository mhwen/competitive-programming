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
		int l, n;
		cin >> l >> n;
		int total = 0;
		for(int i = 0; i < n; i++) {
			total += l+i;
		}
		cout << total << "\n";
	}
}