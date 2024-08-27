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
		vector<int> ans(n);
		vector<vector<int>> best(n, vector<int>(2));
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			a--;
			best[a][i%2] = 1+best[a][(i+1)%2];
			ans[a] = max(ans[a], best[a][i%2]);
		}
		for(int i = 0; i < n; i++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
	}
}