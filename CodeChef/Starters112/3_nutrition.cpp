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
		int n;
		cin >> n;
		map<int, int> seen;
		vector<int> types(n);
		for(int i = 0; i < n; i++) {
			cin >> types[i];
		}
		for(int i = 0; i < n; i++) {
			int b;
			cin >> b;
			seen[types[i]] = max(seen[types[i]], b);
		}
		int ans = 0;
		for(auto i : seen) {
			ans += i.second;
		}
		cout << ans << "\n";
	}
}