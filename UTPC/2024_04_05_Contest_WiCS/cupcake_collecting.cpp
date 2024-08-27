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
	vector<vector<ll>> ans(n, vector<ll>(n, -1));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			ll val;
			cin >> val;
			if(val == -1)
				continue;
			if(i > 0 && ans[i-1][j] != -1)
				ans[i][j] = max(ans[i][j], ans[i-1][j]+val);
			if(j > 0 && ans[i][j-1] != -1)
				ans[i][j] = max(ans[i][j], ans[i][j-1]+val);
			if(i == 0 && j == 0)
				ans[i][j] = 0;
		}
	}
	cout << ans[n-1][n-1] << "\n";
	
}