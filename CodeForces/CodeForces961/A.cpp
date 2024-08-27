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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<int> diagonals;
		for(int i = 1; i <= n-1; i++) {
			diagonals.push_back(i);
			diagonals.push_back(i);
		}
		diagonals.push_back(n);
		sort(all(diagonals));
		int cnt = 0;
		while(k > 0) {
			k -= diagonals.back();
			diagonals.pop_back();
			cnt++;
		}
		cout << cnt << "\n";
	}
}