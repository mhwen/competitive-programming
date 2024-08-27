#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, t;
	cin >> n >> k >> t;
	vector<int> active(n);
	for(int i = 0; i < k; i++) {
		cin >> active[i];
	}
	vector<vector<int>> next(30, vector<int>(n));
	for(int i = 0; i < n; i++) {
		next[0][i] = (i-1+n)%n;
	}
	for(int i = 0; i < k; i++) {
		next[0][active[i]] = (active[(i+1)%k]-1+n)%n;
	}
	for(int bit = 1; bit < (int)next.size(); bit++) {
		for(int i = 0; i < n; i++) {
			next[bit][i] = next[bit-1][next[bit-1][i]];
		}
	}
	vector<int> curr(n);
	iota(curr.begin(), curr.end(), 0);
	for(int bit = 0; bit < (int)next.size(); bit++) {
		if(t&(1<<bit)) {
			for(int i = 0; i < n; i++) {
				curr[i] = next[bit][curr[i]];
			}
		}
	}
	vector<int> ans(n);
	for(int i = 0; i < n; i++) {
		ans[(curr[i]+t)%n] = i;
	}
	for(int i = 0; i < n; i++) {
		cout << ans[i];
		if(i < n-1)
			cout << " ";
	}
	cout << "\n";
}